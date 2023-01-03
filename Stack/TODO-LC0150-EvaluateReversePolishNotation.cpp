class Solution {
    bool isSign(string s){
        return s == "+" || s == "-" || s == "*" || s == "/";
    }
public:
    int evalRPN(vector<string>& tokens) {
        stack<long> st;
        int len = tokens.size();
        if(len == 1) return stoi(tokens[0]);
        int i = 0;

        while(i < len){
           while(!isSign(tokens[i])){
               st.push(stoi(tokens[i]));
               ++i;
           }
           long val2 = st.top();
           st.pop();
           long val1 = st.top();
           st.pop();

           long newVal;
           if(tokens[i] == "+") newVal = val1 + val2;
           else if(tokens[i] == "-") newVal = val1 - val2;
           else if(tokens[i] == "*") newVal = val1 * val2;
           else if(tokens[i] == "/") newVal = val1 / val2;
           st.push(newVal);

           ++i;
        }
        return st.top();
    }
};


//