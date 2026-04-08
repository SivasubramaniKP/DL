struct numbers {
    int a;
    int b;
};

program CALCULATOR_PROG {
    version CALCULATOR_VERS {
        int ADD(numbers) = 1;
        int SUBTRACT(numbers) = 2;
        int MULTIPLY(numbers) = 3;
        int DIVIDE(numbers) = 4;
    } = 1;
} = 0x31234567;
