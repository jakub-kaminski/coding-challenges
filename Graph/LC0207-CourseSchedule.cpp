// question name: LC0207 Course Schedule

// DESCRIPTION:
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
// You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi firs
// if you want to take course ai.
//
//For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
//Return true if you can finish all courses. Otherwise, return false.
//
// Input: numCourses = 2, prerequisites = [[1,0]]
//O utput: true
// Explanation: There are a total of 2 courses to take.
// To take course 1 you should have finished course 0. So it is possible.


// APPROACH:

// FUNCTION NAME: canFinish

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> adjList(numCourses, vector<int>{});
        for (auto &el: prerequisites) {
            adjList[el[0]].push_back(el[1]);
        }

            adjList[i] = {};
        };
    }

    return true;
}

};

TEMPLATE_TEST_CASE("Course Schedule", "[tag1]", Solution) {
//@formatter:off
    auto [msg, numCourses, coursePrereq, expected] = GENERATE_COPY(table<string, int, vector<vector<int>>, bool>({
        {"T1", 2, {{0,1}}, true},
        {"T2", 2, {{0,1},{1,0}}, false},
}));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.canFinish(numCourses, coursePrereq);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
