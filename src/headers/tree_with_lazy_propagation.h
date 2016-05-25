#pragma once
#define MX 1234567

typedef long long int lld;

lld tree[MX * 4];
lld lazy[MX * 4];
int len, r;

void build(int N) {
    len = 1; r = 1;
    while (r <= N) {
        r *= 2;
        len += r;
    }
    int i;
    for (i = len - r + 1; i <= len - r + N; i++) {
        scanf("%lld", tree + i);
    }
    for (i = len - r + N + 1; i <= len; i++) {
        tree[i] = 0;
    }
    for (i = len - r; i >= 1; i--) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
    for (i = 1; i <= len; i++) lazy[i] = 0;
}

void update(int node, int start, int end, int l, int r, lld val) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > r || end < l || start >end) return;
    if (l <= start && end <= r) {
        tree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        return;
    }
    
    int mid = (start + end) / 2;
    update(node * 2, start, mid, l, r, val);
    update(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

lld query(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l) return 0; //out of range
    
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    
    if (l <= start && end <= r) {
        return tree[node];
    }
    
    int mid = (start + end) / 2;
    return  query(node * 2, start, mid, l, r) + query(node * 2 + 1, mid + 1, end, l, r);
}

/*
 Usage
    1) Update
    int b, c, d; scanf("%d %d %d", &b, &c, &d);
    if (b > c) {
        int t = b; b = c; c = t;
    }
    update(1, 0, r- 1, --b, --c, d);


    2) Query
    int b, c; scanf("%d %d", &b, &c);
    if (b > c) {
        int t = b; b = c; c = t;
    }
    printf("%lld\n", query(1, 0, r- 1, --b ,--c));
 */
