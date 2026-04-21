// Problem 043 - Doubly Linked List implementation
#include <bits/stdc++.h>
using namespace std;

namespace LIST {

struct NODE {
    int val;
    NODE* prev;
    NODE* next;
};

static NODE* head = nullptr;
static NODE* tail = nullptr;
static int len = 0;

// Initialize empty list
void Pre() {
    head = nullptr;
    tail = nullptr;
    len = 0;
}

// Move to node at index i (0-based). Assumes 0 <= i < len.
// Returns pointer to the node.
NODE* move(int i) {
    if (i < 0 || i >= len) return nullptr;
    // optimize by direction
    if (i <= len / 2) {
        NODE* cur = head;
        for (int k = 0; k < i; ++k) cur = cur->next;
        return cur;
    } else {
        NODE* cur = tail;
        for (int k = len - 1; k > i; --k) cur = cur->prev;
        return cur;
    }
}

// Insert value x so that it becomes at position i after insertion.
// Valid i in [0, len].
void insert(int i, int x) {
    NODE* node = new NODE{ x, nullptr, nullptr };
    if (len == 0) {
        // inserting into empty list; i must be 0
        head = tail = node;
    } else if (i == 0) {
        // insert before current head
        node->next = head;
        head->prev = node;
        head = node;
    } else if (i == len) {
        // insert after current tail
        node->prev = tail;
        tail->next = node;
        tail = node;
    } else {
        // insert before node currently at index i
        NODE* at = move(i);
        node->next = at;
        node->prev = at->prev;
        if (at->prev) at->prev->next = node;
        at->prev = node;
        if (i == 0) head = node; // redundant safety
    }
    ++len;
}

// Remove element at position i (0 <= i < len)
void remove(int i) {
    if (i < 0 || i >= len || len == 0) return; // guard (inputs promised valid)
    NODE* target = move(i);
    NODE* p = target->prev;
    NODE* n = target->next;
    if (p) p->next = n; else head = n;
    if (n) n->prev = p; else tail = p;
    delete target;
    --len;
}

int Get_length() { return len; }

// Return value at index i; if out of range, return -1
int Query(int i) {
    if (i < 0 || i >= len) return -1;
    NODE* node = move(i);
    return node ? node->val : -1;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE* cur = head;
    bool first = true;
    while (cur) {
        if (!first) cout << ' ';
        cout << cur->val;
        first = false;
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    NODE* cur = head;
    while (cur) {
        NODE* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
    len = 0;
}

} // namespace LIST

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if (!(cin >> n)) return 0;
    int op, x, p, ans;
    LIST::Pre();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                ans = LIST::Get_length();
                cout << ans << '\n';
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << '\n';
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}

