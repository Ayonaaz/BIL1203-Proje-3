int isSolved(int tahta[3][3]) {
    int expectedValue = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            if (i == 2 && j == 2) {
                if (tahta[i][j] == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
            
            if (tahta[i][j] != expectedValue) {
                return 0;
            }
            expectedValue++;
        }
    }
    return 1;
}
