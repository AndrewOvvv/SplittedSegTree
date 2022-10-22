#include <bits/stdc++.h>

using namespace std;


const int MOD = 1e9 + 7;


vector<int> tree;


void
update(int v, int l, int r, int position, int value)
{
    if (l + 1 == r) {
        tree[v] = value;
    } else {
        int m = (l + r) / 2;
        if (position < m) {
            update(2 * v + 1, l, m, position, value);
        } else {
            update(2 * v + 2, m, r, position, value);
        }
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }
}


int
get_max(int v, int l, int r, int ql, int qr)
{
    if (r <= ql || qr <= l) {
        return INT_MIN;
    } else if (ql <= l && r <= qr) {
        return tree[v];
    } else {
        int m = (l + r) / 2;
        return max(get_max(2 * v + 1, l, m, ql, qr), get_max(2 * v + 2, m, r, ql, qr));
    }
}


int
main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int base = atoi(argv[3]);
    int prev = 0, buf;
    buf = 1;

    tree.resize(4 * n);    

    for (int i = 0; i < n; i++) {
        buf = ((prev + buf * base) % MOD + MOD) % MOD;
        prev = buf;
        update(0, 0, n, i, buf);
    }
 
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int type; cin >> type;
        int l, r; cin >> l >> r;
        if (type == 1) {
            l = l % n; r = r % n;
            if (l > r) {
                swap(l, r);
            }
            r++;
            std::cout << get_max(0, 0, n, l, r);
        } else {
            l = l % n;
            update(0, 0, n, l, r);
        }
    }
 
    return 0;
}
