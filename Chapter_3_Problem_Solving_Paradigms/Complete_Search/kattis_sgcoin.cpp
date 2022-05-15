/* Kattis - sgcoin
This is a decently easy precomputation question, just choose a small transaction string (1 char long) to reduce
the cost of each hash operation. I heard that theres a mathematical O(1) solution but looks like im just too dumb for that

Time: O(1), Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

long long H(long long previousHash, string &transaction,
            long long token) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}

pair<int, long long> generate_token(long long previousHash, string transaction){
    for (int i=0;i<1e9-1; i++){
        if (H(previousHash, transaction, i)%((long long) 1e8) == 0){
            return make_pair(i, H(previousHash, transaction, i));
        }
    }

    return make_pair(-1,-1);
}


int main(){

    /* Code to generate token for each possible previous hash value, with transaction == "0"
    for (int i=0;i<=100; i++){
        long long prev_h = i*(1e7);
        auto t = generate_token(prev_h, "0");

        printf("m[%d] = make_pair(%d, %lld);\n", i, t.first, t.second);
    }*/

    pair<int, long long> m[102];
    m[0] = make_pair(99999664, 100000000);
    m[1] = make_pair(29999678, 200000000);
    m[2] = make_pair(59999692, 400000000);
    m[3] = make_pair(89999706, 600000000);
    m[4] = make_pair(19999720, 700000000);
    m[5] = make_pair(49999734, 900000000);
    m[6] = make_pair(79999755, 100000000);
    m[7] = make_pair(9999769, 200000000);
    m[8] = make_pair(39999783, 400000000);
    m[9] = make_pair(69999797, 600000000);
    m[10] = make_pair(99999811, 800000000);
    m[11] = make_pair(29999825, 900000000);
    m[12] = make_pair(59999846, 100000000);
    m[13] = make_pair(89999860, 300000000);
    m[14] = make_pair(19999874, 400000000);
    m[15] = make_pair(49999888, 600000000);
    m[16] = make_pair(79999902, 800000000);
    m[17] = make_pair(9999916, 900000000);
    m[18] = make_pair(39999937, 100000000);
    m[19] = make_pair(69999951, 300000000);
    m[20] = make_pair(99999965, 500000000);
    m[21] = make_pair(29999979, 600000000);
    m[22] = make_pair(59999993, 800000000);
    m[23] = make_pair(90000007, 1000000000);
    m[24] = make_pair(20000028, 100000000);
    m[25] = make_pair(50000042, 300000000);
    m[26] = make_pair(80000056, 500000000);
    m[27] = make_pair(10000070, 600000000);
    m[28] = make_pair(40000084, 800000000);
    m[29] = make_pair(70000098, 1000000000);
    m[30] = make_pair(119, 100000000);
    m[31] = make_pair(30000133, 300000000);
    m[32] = make_pair(60000147, 500000000);
    m[33] = make_pair(90000161, 700000000);
    m[34] = make_pair(20000175, 800000000);
    m[35] = make_pair(50000189, 1000000000);
    m[36] = make_pair(80000210, 200000000);
    m[37] = make_pair(10000224, 300000000);
    m[38] = make_pair(40000238, 500000000);
    m[39] = make_pair(70000252, 700000000);
    m[40] = make_pair(266, 800000000);
    m[41] = make_pair(30000280, 1000000000);
    m[42] = make_pair(60000301, 200000000);
    m[43] = make_pair(90000315, 400000000);
    m[44] = make_pair(20000329, 500000000);
    m[45] = make_pair(50000343, 700000000);
    m[46] = make_pair(80000357, 900000000);
    m[47] = make_pair(10000371, 1000000000);
    m[48] = make_pair(40000392, 200000000);
    m[49] = make_pair(70000406, 400000000);
    m[50] = make_pair(420, 500000000);
    m[51] = make_pair(30000434, 700000000);
    m[52] = make_pair(60000448, 900000000);
    m[53] = make_pair(90000469, 100000000);
    m[54] = make_pair(20000483, 200000000);
    m[55] = make_pair(50000497, 400000000);
    m[56] = make_pair(80000511, 600000000);
    m[57] = make_pair(10000525, 700000000);
    m[58] = make_pair(40000539, 900000000);
    m[59] = make_pair(70000560, 100000000);
    m[60] = make_pair(574, 200000000);
    m[61] = make_pair(30000588, 400000000);
    m[62] = make_pair(60000602, 600000000);
    m[63] = make_pair(90000616, 800000000);
    m[64] = make_pair(20000630, 900000000);
    m[65] = make_pair(50000651, 100000000);
    m[66] = make_pair(80000665, 300000000);
    m[67] = make_pair(10000679, 400000000);
    m[68] = make_pair(40000693, 600000000);
    m[69] = make_pair(70000707, 800000000);
    m[70] = make_pair(721, 900000000);
    m[71] = make_pair(30000742, 100000000);
    m[72] = make_pair(60000756, 300000000);
    m[73] = make_pair(90000770, 500000000);
    m[74] = make_pair(20000784, 600000000);
    m[75] = make_pair(50000798, 800000000);
    m[76] = make_pair(80000812, 1000000000);
    m[77] = make_pair(10000833, 100000000);
    m[78] = make_pair(40000847, 300000000);
    m[79] = make_pair(70000861, 500000000);
    m[80] = make_pair(875, 600000000);
    m[81] = make_pair(30000889, 800000000);
    m[82] = make_pair(60000903, 1000000000);
    m[83] = make_pair(90000924, 200000000);
    m[84] = make_pair(20000938, 300000000);
    m[85] = make_pair(50000952, 500000000);
    m[86] = make_pair(80000966, 700000000);
    m[87] = make_pair(10000980, 800000000);
    m[88] = make_pair(40000994, 1000000000);
    m[89] = make_pair(70001015, 200000000);
    m[90] = make_pair(1029, 300000000);
    m[91] = make_pair(30001043, 500000000);
    m[92] = make_pair(60001057, 700000000);
    m[93] = make_pair(90001071, 900000000);
    m[94] = make_pair(20001085, 1000000000);
    m[95] = make_pair(50001106, 200000000);
    m[96] = make_pair(80001120, 400000000);
    m[97] = make_pair(10001134, 500000000);
    m[98] = make_pair(40001148, 700000000);
    m[99] = make_pair(70001162, 900000000);
    m[100] = make_pair(1176, 1000000000);

    long long prev_h;
    cin >> prev_h;
    prev_h /= 1e7;

    int token_1 = m[prev_h].first;
    long long hash_1 = m[prev_h].second;
    cout << 0 << " " << token_1 << endl;
    hash_1/=1e7;
    cout << 0 << " " << m[hash_1].first << endl;
    

    return 0;
}