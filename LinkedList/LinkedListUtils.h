#ifndef CPP_SOLUTIONS_LINKEDLISTUTILS_H
#define CPP_SOLUTIONS_LINKEDLISTUTILS_H

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* vecToList(vector<int> v){
    ListNode* prev = new ListNode;
    ListNode* head = prev;
    if(v.size() == 0){
        head = nullptr;
    }
    else{
        for(int i = 0; i < v.size(); ++i){
            if(i ==0){ prev->val = v[i]; }
            else{
                ListNode* node = new ListNode(v[i]);
                prev->next = node;
                prev = node;
            }
        }
    }
    return head;
}

vector<int> listToVec(ListNode* head){
    vector<int> result;
    while(head != nullptr){
        result.push_back(head->val);
        head=head->next;
    }
    return result;
}

ListNode* vecToListControlledConnections(vector<array<int,2>> v){
    int len = v.size();
    if(len == 0) return nullptr;
    vector<ListNode*> nodes;
    nodes.reserve(len);
    for(int i = 0; i < len; ++i){
        ListNode* tmp = new ListNode(v[i][0]);
        nodes.push_back(tmp);
    }
    for(int i = 0; i < len; ++i){
        if(v[i][1] == -1) nodes[i]->next = nullptr;
        else nodes[i]->next = nodes[v[i][1]];
    }
    return nodes[0];
}
#endif //CPP_SOLUTIONS_LINKEDLISTUTILS_H

