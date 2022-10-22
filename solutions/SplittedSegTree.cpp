#include <bits/stdc++.h>
#include <limits.h>

using namespace std;

const int MOD = 1e9 + 7;

int
max(int x, int y)
{
    if (x > y) {
        return x;
    } else {
        return y;
    }
}


struct SQRT_Tree {
    int n;
    int in_size;
    vector<int> tree;

    SQRT_Tree (int n, int cnt_split, int resize_value) {
        this->n = n;
        this->in_size = cnt_split;
        this->tree.resize(resize_value, INT_MIN);
    }

    void build(int v, int l, int r, vector<int> &array, int size) {
        if (l + 1 == r && l < (int)array.size()) {
            this->tree[v] = array[l];
        } else if (l < (int)array.size()) {
            for (int i = 1; i <= this->in_size; ++i) {
                build(this->in_size * v + i, l + size * (i - 1), l + size * i, array, size / this->in_size);
                this->tree[v] = max(this->tree[v], this->tree[this->in_size * v + i]);
            }
        }
    }

    void update_list(int v, int l, int r, int size, int position, int value) {
        if (l + 1 == r) {
            this->tree[v] = value;
        } else {
            int block = (position - l) / size + 1;
            update_list(this->in_size * v + block, l + size * (block - 1), l + size * block, size / this->in_size, position, value);
            this->tree[v] = max(this->tree[v], this->tree[this->in_size * v + block]);
        }
    }

    void update(int v, int l, int r, int size, int position, int value) {
        if (l + 1 == r) {
            this->tree[v] = value;
        } else {
            int block = (position - l) / size + 1;
            update(this->in_size * v + block, l + size * (block - 1), l + size * block, size / this->in_size, position, value);
            this->tree[v] = INT_MIN;
            for (int i = 1; i <= this->in_size; ++i) {
                this->tree[v] = max(this->tree[v], this->tree[this->in_size * v + i]);
            }
        }
    }

    int get_max(int v, int l, int r, int size, int ql, int qr) {
        if (r <= ql || qr <= l) {
            return INT_MIN;
        } else if (ql <= l && r <= qr) {
            return this->tree[v];
        } else {
            int result = INT_MIN;
            for (int i = 1; i <= this->in_size; i++) {
                result = max(result, get_max(this->in_size * v + i, l + (i - 1) * size, l + i * size, size / this->in_size, ql, qr));
            }
            return result;
        }
    }
};


int
main(int argc, char *argv[])
{
    int n = atoi(argv[1]), cnt_split = MY_K;
    int base = atoi(argv[3]);
    int prev = 0, buf;
    int size = 1, resize_value = 0;

    while (size < n) {
        resize_value += size;
        size *= cnt_split;
    }
    resize_value += n + 10;

    SQRT_Tree T(n, cnt_split, resize_value);



    buf = 1;
    for (int i = 0; i < n; i++) {
        buf = ((prev + buf * base) % MOD + MOD) % MOD;
        prev = buf;
        T.update_list(0, 0, size, size / cnt_split, i, buf);
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
            std::cout << T.get_max(0, 0, n, size / cnt_split, l, r);
        } else {
            l = l % n;
            T.update(0, 0, n, size / cnt_split, l, r);
        }
    }

    return 0;
}
