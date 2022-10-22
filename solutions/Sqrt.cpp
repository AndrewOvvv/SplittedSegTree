#include <bits/stdc++.h>
#include <limits.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 4e6 + 5;

int
main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int base = atoi(argv[3]);
    int prev = 0, buf;
    int SIZE = sqrt(n) + 2;
    vector<int> a(n);
    vector<int> blocks(SIZE, INT_MIN);
    buf = 1;
    for (int i = 0; i < n; i++) {
        buf = ((prev + buf * base) % MOD + MOD) % MOD;
        prev = buf;
        a[i] = buf;
        blocks[i / SIZE] = max(blocks[i / SIZE], a[i]);
    }
    
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int type; cin >> type;
        int l, r; cin >> l >> r;
        if (type == 1) {
            //get_max
            l %= n; r %= n;
            if (l > r) {
                swap(l, r);
            }
            r++;
            int ans = INT_MIN;
            for (int i = (l / SIZE + 1); i < (r / SIZE); i++) {
                ans = max(ans, blocks[i]);
            }
            for (int i = l; i < min((l / SIZE + 1) * SIZE, r); i++) {
                ans = max(ans, a[i]);
            }
            if (l / SIZE != r / SIZE) {
                for (int i = (r / SIZE) * SIZE; i < r; i++) {
                    ans = max(ans, a[i]);
                }
            }
            cout << ans;
        } else {
            //update
            l %= n;
            a[l] = r;
            blocks[l / SIZE] = INT_MIN;
            for (int i = (l / SIZE) * SIZE; i < min((l / SIZE + 1) * SIZE, n); i++) {
                blocks[l / SIZE] = max(blocks[l / SIZE], a[i]);
            }
        }
    }
    return 0;
}
