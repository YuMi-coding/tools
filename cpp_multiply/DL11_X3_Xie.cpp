/*
  COSC 1337 Exam 3 Lab portion, part 3
  Name:JIngyuan Xie

  Submit DLS_X3_Xie.cpp
    after changing DL (Distance Learning Section) to: DL11, DL7 or DL9
    and Lastname to: your last name
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

enum Personal_t{FIRST, LAST, FOOD, CALLS, NONE};

// Part 1A, 1B, 1C, 1D: create function myself, string myself(Personal_t)
string myself(Personal_t a){
	static int calls=0;
	calls++;
	switch(a){
		case FIRST:
			return "Jingyuan";
			break;
		case LAST:
			return "Xie";
			break;
		case FOOD:
			return "BBQ rib";
			break;
		case CALLS:
			return to_string(calls);
			break;
	}
}
string myself(){
	return "Jingyuan Xie";
}

void part1() {
  // ------------------ section below is provided for testing, it is called from main
  cout<<"part 1:\n";
  // Testing for part 1D, 2 points, code provided
  cout<<"part 1E: myself testing:\n";

  cout << myself(FIRST) << endl;
  cout << myself(LAST) << endl;
  cout << myself(FOOD) << endl;
  cout << myself() << endl;
  cout << myself(CALLS)<<endl;
  cout << endl;
}

// Put your code for part 2A, 2B, 2C, 2D here, class HotTub
class HotTub {
  private:
  	float diameter;
  	float depth;
  	float rate;

  public:
  	HotTub(float dia=3,float dep=2,float r=50){
  		if (dia > 100)	diameter=100;
  		else if(dia<3) diameter=3;
  		else diameter=dia;
  		
  		if (dep > 100)	depth=100;
  		else if(dep<2) depth=2;
  		else depth=dep;
  		
  		if (r > 1000)	rate=1000;
  		else if(r<50) rate=50;
  		else rate=r;
	}

	
	const string company_name="Jing's";

	HotTub operator++(){
  	diameter+=1;
  	return *this;
  }
  	HotTub operator++(int){
  	HotTub temp=*this;
  	++*this;
  	return temp;
  }

HotTub operator+(const HotTub& b)
   {
      HotTub hottub;
      hottub.diameter = this->diameter + b.diameter;
      hottub.depth = this->depth + b.depth;
      hottub.rate = (this->rate + b.rate)/2;
      return hottub;
   }
	
	float get_gallons()const {
		float gallons=M_PI*(diameter/2)*(diameter/2)*depth/7.48;
		return gallons;
	}  
	
	float get_cost()const {
		float cost=get_gallons()*rate;
		return cost;
	}
	
	string get_name()const {
		string name=company_name;
		return name;
	}
	


};


void showHotTubInfo(const HotTub &hot_tub) {
  cout << hot_tub.get_gallons() << "  ";  // Uncomment when ready for testing
  cout << hot_tub.get_cost() << "  ";     // Uncomment when ready for testing
  cout << hot_tub.get_name() << "  ";     // Uncomment when ready for testing
  cout << endl;
}

void part2() {
  cout<<"part 2:\n";
  cout<<"part 2E: HotTub testing:\n";
  //testing code for HotTub construction: construct 4 instances of HotTub
  HotTub hot_tub1(5.5, 2.2, 95.50);  // Uncomment when ready for testing
  HotTub hot_tub2(4, 3.5);           // Uncomment when ready for testing
  HotTub hot_tub3(6.5) ;             // Uncomment when ready for testing
  HotTub hot_tub4();                 // Uncomment when ready for testing
  //For any class HotTub constructors that do not work, keep it commented out.

  //testing code for HotTub getters: call function showHotTubInfo for each HotTub instance
  showHotTubInfo(hot_tub1); // Uncomment when ready for testing
  showHotTubInfo(hot_tub2); // Uncomment when ready for testing
  showHotTubInfo(hot_tub3); // Uncomment when ready for testing
  //showHotTubInfo(hot_tub4); // Uncomment when ready for testing
  cout << endl;
}


void part3() {
  cout<<"part 3:\n";
  cout<<"part 3D: testing pointers, dynamic memory using HotTub\n";
  // complete (add code to show addresses) and uncomment when ready...
  /*
    Dynamically allocate one instance of class HotTub. Construct this using a diameter value
    of the first digit of your ACCeID, a depth value of the second digit of your ACCeID,
    and a rate value of the third forth.fifth sixth digit. For example, if your
    ACCeID is: a1234567, create a HotTub(1, 2, 34.56).
  */
  HotTub* my_hot_tub=NULL;
  my_hot_tub=new HotTub(1,9,02.05);

  cout << "single HotTub is at address: " << &my_hot_tub;

  // See instructions for HotTub array.
  HotTub* hot_tub_array=NULL;
  hot_tub_array=new HotTub[2000];
  cout << "first element in HotTub array at address:  " << &hot_tub_array[0];
  cout << "middle element in HotTub array at address:  " << &hot_tub_array[999];
  cout << "last element in HotTub array at address:  " << &hot_tub_array[1999];

  // Deallocate memory allocated above
  delete my_hot_tub;
  delete []hot_tub_array;
  my_hot_tub=NULL;
  hot_tub_array=NULL;

  cout<<endl;
};


HotTub add(HotTub, HotTub); // incomplete prototype to start operator+ for class HotTub, goes with Part 4



void part4() {
  // Below is testing code for part 4; it will be called from main. No changes needed.
  cout<<"part 4:\n";
  cout<<"part 4C: testing operator++\n";

  HotTub hottub();
  for (int i{}; i<3; ++i) {
   showHotTubInfo(hottub);
   hottub++;
  }

  cout << endl;


  cout<<"part 4C: testing operator+\n";
  HotTub hot_tub1, hot_tub2;
  HotTub hot_tub3 = hot_tub1 + hot_tub2;
  showHotTubInfo(hot_tub1);
  showHotTubInfo(hot_tub2);
  showHotTubInfo(hot_tub3);
  cout << endl;

};

int sum(int limit, int skip_distance=1) {
  int total{};
  if (limit >=0) {
    for (int i{}; i<limit; i+=skip_distance) {
      total+=i;
    }
  }
  else {
    for (int i{}; i>limit; i-=skip_distance) {
      total+=i;
    }
  }

  return total;
}

int sum_recurse(int limit, int skip_distance=1){
	int a=0;
	if (limit > skip_distance) {
		a=sum_recurse(limit-skip_distance,skip_distance);
	}
	else if(limit < -skip_distance){
		a=sum_recurse(limit+skip_distance,skip_distance);
	}
	return a+limit;
}

void part5() { // recursion
  cout<<"part 5B: testing sum_recurse(int limit, int skip_distance).\n";
   cout << sum_recurse(5) << endl;
   cout << sum_recurse(-3) << endl;
   cout << sum_recurse(20, 4) << endl;
   cout << sum_recurse(-10, 3) << endl;
  cout << endl;
}

// Part 6 is to Compile, run, capture program output, and paste test output at bottom


void part7() { // EXTRA CREDIT
  cout<<"part 7: (optional extra credit)\n";
  // ----------------- This section allocates some memory, but never deletes it
  class Horse { // make instances of class Horse, optimized to make allow a list of horses
    string name;     // name of the horse, defaults to ""
    double height{}; // height of the horse, defaults to 0.0
    Horse *next{};   // pointer to the next horse, defaults to nullptr
    public:
      Horse(string name, double height, Horse *next=nullptr) {
        this->name=name; this->height=height; this->next=next;
      }
      Horse *get_next() const {
        return next;
      };
  };

  char *p_buffer = new char[50000];
  int *p_int = new int;
  Horse *p_horses = new Horse("Zella", 50, new Horse("Yankee", 60));
  Horse *p_paddock = new Horse[3]{Horse("Alex", 70), Horse("Buster", 80), Horse("Crippix", 90)};
  //---------------------------------------------------------------------
  // Put your code for part 7 here: Delete any memory left on the heap above to prevent memory leak
  // Hint: there are 5 new, so there must be 5 delete. No need to reset pointers to nullptr.
  // No need to display anything to output, just provide appropriate delete statements.

};

int main() {
  // No new code goes in main. Put all new code where designated in the parts above.
  const int COURSE {1337};
  cout<<"COSC " << std::to_string(COURSE) << " Exam 3 Part 3 Start...\n\n"; // example of std::to_string()
  part1();
  part2();
  part3();
  part4();
  part5();
  // part 6 is to test
  part7();  // EXTRA CREDIT: free up (delete) memory to prevent memory leak
  cout<<"\n...End.\n";
	return 0;
}
/* Put the test output here.
COSC 1337 Exam 3 Part 3 Start...

part 1:
part 1E: myself testing:
Jingyuan
Xie
BBQ rib
Jingyuan Xie
4

part 2:
part 2E: HotTub testing:
6.98773  667.329  Jing's
5.87999  293.999  Jing's
8.87248  443.624  Jing's

part 3:
part 3D: testing pointers, dynamic memory using HotTub
single HotTub is at address: 0x7bfd80first element in HotTub array at address:  0xaa2498middle element in HotTub array at address:  0xaadfe8last element in HotTub array at address:  0xab9b68
part 4:
part 4C: testing operator++

part 4C: testing operator+
1.89  94.4998  Jing's
1.89  94.4998  Jing's
15.12  755.998  Jing's

part 5B: testing sum_recurse(int limit, int skip_distance).
15
-6
60
-22

part 7: (optional extra credit)

...End.

--------------------------------
Process exited after 0.05749 seconds with return value 0
*/