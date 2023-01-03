class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;

        ListNode* oddHead = head;
        ListNode* evenHead = head->next;

        ListNode* oddBegin = oddHead;
        ListNode* evenBegin = evenHead;


        // 1 2 3 4 5
        //   ^ ^
        int iter = 0;
        while(true){
            iter++;
            if(evenHead->next == nullptr){
                oddHead->next = evenBegin;
                return oddBegin;
            }

            oddHead->next = evenHead->next;
            oddHead = oddHead->next;

            if(oddHead->next == nullptr){
                evenHead->next = nullptr;
                oddHead->next = evenBegin;
                return oddBegin;
            };

            evenHead->next = oddHead->next;
            evenHead = evenHead->next;
        }

        return oddBegin;
    }
};