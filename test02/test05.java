import java.util.*;

/*
    Dynamic programming
    TEST01
    1 1 1 0 1   =>   1 1 1 0 0
    1 1 1 1 1   =>   1 2 3 3 3
    TEST02
    1 1 0 1           1 1 0 0
    1 1 1 0     =>    1 2 2 0
    0 1 1 1           0 2 4 4
*/

public class Test05 {
     public static void main(String []args){
        // Test00
        List<List<Integer>> A = new ArrayList<>();
        List<Integer> r0;
        List<Integer> r1;
        List<Integer> r2;
        System.out.println(Solution.solution(A));
        // Test01
        A = new ArrayList<>();
        r0 = Arrays.asList(1, 1, 1, 0, 1);
        r1 = Arrays.asList(1, 1, 1, 1, 1);
        A.add(r0);
        A.add(r1);
        System.out.println(Solution.solution(A));
        // Test02
        A = new ArrayList<>();
        r0 = Arrays.asList(1, 1, 0, 1);
        r1 = Arrays.asList(1, 1, 1, 0);
        r2 = Arrays.asList(0, 1, 1, 1);
        A.add(r0);
        A.add(r1);
        A.add(r2);
        System.out.println(Solution.solution(A));
     }
}

class Solution {
    // Use dynamic programming, O(m * n)
    public static int solution(List<List<Integer>> A) {
        if (A.size() == 0) return 0;
        if (A.get(0).get(0) == 0 || A.get(A.size() - 1).get(A.get(0).size() - 1) == 0) return 0;
        int[][] arr = new int[A.size()][A.get(0).size()];
        arr[0][0] = A.get(0).get(0);
        // Initialize A[i][0]
        for (int i = 1; i < arr.length; i++) {
            if (arr[i - 1][0] == 0) arr[i][0] = 0;
            else arr[i][0] = A.get(i).get(0);
        }
        // Initialize A[0][j]
        for (int j = 1; j < arr[0].length; j++) {
            if (arr[0][j - 1] == 0) arr[0][j] = 0;
            else arr[0][j] = A.get(0).get(j);
        }
        // arr[i][j] = arr[i - 1][j] + arr[i][j - 1]
        for (int i = 1; i < arr.length; i++) {
            for (int j = 1; j < arr[0].length; j++) {
                if (A.get(i).get(j) == 0) 
                    arr[i][j] = 0;
                else
                    arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
            }
        }
        return arr[arr.length - 1][arr[0].length - 1];
    }
}
