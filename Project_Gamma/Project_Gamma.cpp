//ME 493 Project Gamma
//Etzal Corona
//Buddy Coded with Ethan Skemp and Roberto Jimenez

#include<cstdlib>
#include<iostream>
#include<vector>
#include<assert.h>
#include<ctime>
#include<cmath>
#include<algorithm>

#define ECRand (long double)rand()/RAND_MAX
#define city_numbers 100
#define population_size 100
#define numbers_to_swap 3
#define max_iterations 100

using namespace std;


class cities {
	static int count;
public:

	int x;
	int y;
	int index;

	cities();
	cities(int x , int y);
};



class policy {
public:

	int citylist[city_numbers];
	policy();
	policy(const policy &);
};


//Initializes count
int cities::count = 0;

//Findig distance between cities
double citydistance(cities citya, cities cityb) {
	return pow(pow(citya.x - cityb.x, 2) + (citya.y - cityb.y, 2), 0.5); //Pythagorean
};




//random city locations
cities::cities() {
	x = (long double) ECRand * 100;
	y = (long double) ECRand * 100;
	index = count;
	count ++;
}


//asigned city locations
cities::cities(int xa, int ya) {
	x = xa;
	y = ya;
	index = count;
	count++;
}

policy::policy() {
	for (int i = 0; i < city_numbers; i++){
		citylist[i] = 0;
	}
};


policy::policy(const policy & in ) {
	for (int i = 0; i < city_numbers; i++) {
		citylist[i] = in.citylist[i];
	}
}


//.......................................................... Prototypes  .......................................................................

//populate cities function prototype
void populate(vector<cities> & citydirectory);

//Policies prototype
void create_policies(vector<policy> & policies);

//Fitness prototype
double get_fitness(policy in_policy, vector <cities> citylista);

//March Madness Prototype
void March_Madness(vector <policy> & policy_list, vector <cities> citylist);

//Swapping prototype
void swap(policy & in_policy, int number_swaps);

//Mutate prototype
void mutate(vector <policy> & in_policy_vec);

//Best policy prototype
double best_policy(vector<policy>vec_policies, vector<cities>vec_cities);



// .......................................................... MAIN ............................................................................
int main() {

	srand(time(NULL));

	vector<cities>citydirectory;
	populate(citydirectory);
	vector<policy>population_policy;
	create_policies(population_policy);



	for (int i = 0; i < max_iterations; i++) {
		cout << i << "\t:" << best_policy( population_policy , citydirectory ) << endl;
		
		//for (int j = 0; j < population_size; j++) {
		//	cout << j << "\t" << get_fitness(population_policy[j], citydirectory) << endl;

		//}
		
		March_Madness(population_policy, citydirectory);
		mutate(population_policy);
	}
	int x;
	cin >> x;

}



//.......................................................... Functions  .......................................................................

void populate(vector<cities> & citydirectory){
	int citymodel = 0;
	for ( ; citymodel < city_numbers; citymodel++) {
		cities in_city;
		citydirectory.push_back(in_city);
	}
}




void create_policies(vector<policy> & policies) {
	policy instance;
	policies.push_back(instance);
	for (int i = 0; i < city_numbers; i++) {
		policies[0].citylist[i] = i;
	}
	for (int i = 1; i < population_size; i++) {
		policy temp_policy(policies[0]);
		swap(temp_policy, city_numbers);
		policies.push_back(temp_policy);
	}
}





double get_fitness(policy in_policy, vector <cities> citylista) {
	double counter = 0;
	for (int i = 1; i < city_numbers; i++) {
		counter += citydistance(citylista[in_policy.citylist[i - 1]], citylista[in_policy.citylist[i]]);
	}
	return counter;
}



//Binary tournament
void March_Madness(vector <policy> & policy_list, vector <cities> citylist) {
	//cout << "size before: " << policy_list.size() << endl;
	for (int i = population_size-2; i>=0; i -= 2) {
		if (get_fitness(policy_list[i], citylist) < get_fitness(policy_list[i + 1], citylist)) {
			policy_list.erase(policy_list.begin() + i + 1);
		}
		else{
			policy_list.erase(policy_list.begin() +i );
		}
	}
	//cout << "size after: " << policy_list.size() << endl;
}


//Swapping function
void swap(policy & in_policy, int number_swaps) {
	int pos1 = 0;
	int pos2 = 0;
	while ((pos1 == 0) || (pos2 == 0) || (pos1 == pos2)) {
		pos1 = rand() % city_numbers;
		pos2 = rand() % city_numbers;
	}
	for (; number_swaps > 0; number_swaps--) {
		swap(in_policy.citylist[pos1], in_policy.citylist[pos2]);
	}
}



//Mutate functions
void mutate(vector <policy> & in_policy_vec) {
	//cout << "size before m: " << in_policy_vec.size() << endl;
	for (int i = population_size / 2 - 1; i >= 0; i--) {
		policy temp_policy(in_policy_vec[i]);
		swap(temp_policy, numbers_to_swap);
		in_policy_vec.push_back(temp_policy);
	}
	//cout << "size after m: " << in_policy_vec.size() << endl;
}



//Best policy function
double best_policy(vector<policy>vec_policies, vector<cities>vec_cities) {
	double best_length = get_fitness(vec_policies[0], vec_cities);
	for (int i = 1; i < population_size; i++) {
		if (get_fitness(vec_policies[i], vec_cities) < best_length) {
			best_length = get_fitness(vec_policies[i], vec_cities);
		}
	}
	return best_length;
}