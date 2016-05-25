#pragma once
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

template<typename type>
type ccw(const pair<type, type> &O, const pair<type, type> &A, const pair<type, type> &B) {
   return (type) (A.first - O.first) * (B.second - O.second)
    - (type) (A.second - O.first) * (B.second- O.first);
}

//note that result.front == result.back
template<typename type>
vector<pair<type, type>> convex_hull(vector<pair<type, type>> points) {
    int k=0;
    vector<pair<type, type>> result(2*points.size());
    sort(points.begin(), points.end(),
         [](pair<type, type> l, pair<type, type> r) {
             
             //CHANGE HERE to determine the first point
             return l.second > r.second || (! (l.fist < r.first));
         });
    for (int i=0; i< points.size(); i++) {
        while(k>=2 && ccw(result[k-2], result[k-1], points[i]) <= 0) {
            k--;
        }
        result[k++] = points[i];
    }
    for (int i=points.size()-2, t= k+1; i>=0; i--) {
        while(k>= t && ccw(result[k-2], result[k-1], points[i] <= 0)) {
            k--;
        }
        result[k++] = points[i];
    }
    result.resize(k);
    return result;
}