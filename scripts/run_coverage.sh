#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${BUILD_DIR:-build-coverage}"
REPORT_DIR="${BUILD_DIR}/coverage-report"
CTEST_REPORT="${BUILD_DIR}/ctest-report.xml"
COVERAGE_INFO="${BUILD_DIR}/coverage.info"
COVERAGE_FILTERED_INFO="${BUILD_DIR}/coverage.filtered.info"
CLEAN_BUILD=0
OPEN_REPORT=0

usage() {
    cat <<EOF
Usage: $0 [--clean] [--open]

Options:
  --clean   Remove ${BUILD_DIR} before configuring.
  --open    Open the generated HTML coverage report after completion.

Environment:
  BUILD_DIR Override build directory. Default: build-coverage
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --clean)
            CLEAN_BUILD=1
            shift
            ;;
        --open)
            OPEN_REPORT=1
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 2
            ;;
    esac
done

require_command() {
    if ! command -v "$1" >/dev/null 2>&1; then
        echo "Missing required command: $1" >&2
        echo "Install dependencies with: brew install gcc lcov cmake" >&2
        exit 1
    fi
}

find_latest_gcc_version() {
    local brew_prefix
    brew_prefix="$(brew --prefix)"

    find "${brew_prefix}/bin" -maxdepth 1 \( -type f -o -type l \) -name 'gcc-[0-9]*' \
        | sed 's/.*gcc-//' \
        | sort -n \
        | tail -1
}

require_command brew
require_command cmake
require_command ctest
require_command lcov
require_command genhtml

BREW_PREFIX="$(brew --prefix)"
GCC_VERSION="${GCC_VERSION:-$(find_latest_gcc_version)}"

if [[ -z "${GCC_VERSION}" ]]; then
    echo "No Homebrew GCC found. Install it with: brew install gcc" >&2
    exit 1
fi

CC="${BREW_PREFIX}/bin/gcc-${GCC_VERSION}"
CXX="${BREW_PREFIX}/bin/g++-${GCC_VERSION}"
GCOV="${BREW_PREFIX}/bin/gcov-${GCC_VERSION}"

for tool in "${CC}" "${CXX}" "${GCOV}"; do
    if [[ ! -x "${tool}" ]]; then
        echo "Expected tool is not executable: ${tool}" >&2
        exit 1
    fi
done

cd "${REPO_ROOT}"

if [[ "${CLEAN_BUILD}" -eq 1 ]]; then
    echo "Cleaning ${BUILD_DIR}"
    cmake -E rm -rf "${BUILD_DIR}"
fi

echo "Using GCC ${GCC_VERSION}"
echo "Configuring ${BUILD_DIR}"
cmake -S . -B "${BUILD_DIR}" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_C_COMPILER="${CC}" \
    -DCMAKE_CXX_COMPILER="${CXX}" \
    -DCMAKE_C_FLAGS="--coverage -O0 -g" \
    -DCMAKE_CXX_FLAGS="--coverage -O0 -g" \
    -DCMAKE_EXE_LINKER_FLAGS="--coverage"

echo "Building"
cmake --build "${BUILD_DIR}"

echo "Resetting coverage counters"
lcov --directory "${BUILD_DIR}" --zerocounters >/dev/null

echo "Running tests"
ctest --test-dir "${BUILD_DIR}" \
    --output-on-failure \
    --output-junit "${CTEST_REPORT}"

echo "Capturing coverage"
lcov --capture \
    --directory "${BUILD_DIR}" \
    --gcov-tool "${GCOV}" \
    --ignore-errors inconsistent \
    --output-file "${COVERAGE_INFO}"

echo "Filtering coverage"
lcov --remove "${COVERAGE_INFO}" \
    "*/_deps/*" \
    "*/tests/*" \
    "/Applications/*" \
    "/Library/*" \
    "/opt/homebrew/*" \
    --gcov-tool "${GCOV}" \
    --ignore-errors unused \
    --output-file "${COVERAGE_FILTERED_INFO}"

echo "Generating HTML report"
genhtml "${COVERAGE_FILTERED_INFO}" \
    --output-directory "${REPORT_DIR}"

REPORT_INDEX="${REPO_ROOT}/${REPORT_DIR}/index.html"
echo
echo "Done."
echo "CTest report: ${REPO_ROOT}/${CTEST_REPORT}"
echo "Coverage report: ${REPORT_INDEX}"

if [[ "${OPEN_REPORT}" -eq 1 ]]; then
    open "${REPORT_INDEX}"
fi
