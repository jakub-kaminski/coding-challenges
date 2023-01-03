// QUESTION NAME: LC0901 Online Stock Span

// DESCRIPTION:
// Design an algorithm that collects daily price quotes for some stock
// and returns the span of that stock's price for the current day.
//
// The span of the stock's price today is defined as the maximum number
// of consecutive days (starting from today and going backward)
// for which the stock price was less than or equal to today's price.
// For example, if the price of a stock over the next 7 days were
// [100,80,60,70,60,75,85], then the stock spans would be [1,1,1,2,1,4,6].
// Implement the StockSpanner class:
//
// StockSpanner() Initializes the object of the class.
// int next(int price) Returns the span of the stock's price given that today's price is price.
//
// Input
// ["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
// [[], [100], [80], [60], [70], [60], [75], [85]]
// Output
// [null, 1, 1, 1, 2, 1, 4, 6]
//
// Explanation
// StockSpanner stockSpanner = new StockSpanner();
// stockSpanner.next(100); // return 1
// stockSpanner.next(80);  // return 1
// stockSpanner.next(60);  // return 1
// stockSpanner.next(70);  // return 2
// stockSpanner.next(60);  // return 1
// stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75) were less than or equal to today's price.
// stockSpanner.next(85);  // return 6
//
// 1 <= price <= 10^5
// At most 10^4 calls will be made to next.
//
// https://leetcode.com/problems/online-stock-span/

// APPROACH:
// Linked list linking to previous node and node after the span

// FUNCTION NAME: StockSpanner

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>
#include "LinkedListUtils.h"

using namespace std;

class MyListNode{
   public:
    int val;
    int span;
    MyListNode* prev;
    MyListNode* scopeEnd;
    MyListNode(int v){
       val = v;
       prev = nullptr;
       scopeEnd = nullptr;
    }
};

class StockSpanner {
    MyListNode* head;
public:
    StockSpanner() {
        head = new MyListNode(-1);
    }

    int next(int price) {
        // first run
       if( head->val == -1){
          head->val = price;
          head->span = 1;

          head->prev = nullptr;
          head->scopeEnd = nullptr;

          return head->span;
       }

        if(head->val > price){
            MyListNode* node = new MyListNode(price);
            node->prev = head;
            node->scopeEnd = head;
            node->span = 1;
            head = node;

            return head->span;
        }
        else{
            MyListNode* node = new MyListNode(price);
            node->prev = head;
            head = node;

            MyListNode* n = head->prev;
            int span = 1;

            while(n != nullptr && n->val <= price){
               span += n->span;
               n = n->scopeEnd;
            }

            head->span = span;
            head->scopeEnd = n;

            return head->span;
        }
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */