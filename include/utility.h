class Utility {
private:
    static int PrivateStaticMethod(int x) {
        return x * 2;
    }
    
    // 使用测试类作为友元
    friend class UtilityTestAccess;
};

// 测试访问类
class UtilityTestAccess {
public:
    static int CallPrivateMethod(int x) {
        return Utility::PrivateStaticMethod(x);
    }
};