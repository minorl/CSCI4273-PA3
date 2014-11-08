#include <queue>
#include <iostream>



template <class T, class C,class S > 
  class removable_priority_queue: public std::priority_queue<T,C,S>
  {
  public:
    void remove(int target){
	    for (unsigned i=0; i<this->c.size(); ++i){
	    	if(this->c[i].id == target){
	    		this->c.erase(this->c.begin() + i);
	    		break;
	    	}
	    }
    } 
}; 

struct tester
{
	int id;
	int pd;
};
class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=true)
    {reverse=revparam;}
  bool operator() (const struct tester& lhs, const struct tester&rhs) const
  {
    if (reverse) return (lhs.id>rhs.id);
    else return (lhs.id<rhs.id);
  }
};
int main()
{
    // reservable_priority_queue<int> q;
    // q.reserve(10000);
    // std::cout << q.capacity() << '\n';
    removable_priority_queue<struct tester,std::vector<struct tester>,mycomparison> q;
    struct tester first ={id: 1, pd:2};
    struct tester second ={id: 2, pd:2};
    struct tester third ={id: 3, pd:2};
    struct tester fourth ={id: 4, pd:2};
    struct tester fifth ={id: 5, pd:2};
    q.push(fifth);
    q.push(fourth);
    q.push(first);
    q.push(second);
    q.push(third);
    std::cout << q.size() << std::endl;
    std::cout << "top id:" << q.top().id << std::endl;
    std::cout << "removing id 2" << std::endl;
    q.remove(5);
    
    while (!q.empty()){
    	std::cout << "top id:" << q.top().id << std::endl;
     	q.pop();
  	}


}



