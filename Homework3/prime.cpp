#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
i#include <cmath>
#include <ctime>

using namespace std;	

bool greaterBandB(vector<int> z, vector<int> c){

	int z_size = z.size();
	int c_size = c.size();

	if(z_size > c_size){
		for(int i = 0; i < z_size - c_size; i++){
			c.push_back(0);
		}
	}
	else if(c_size > z_size)
	{
		for(int i = 0; i < c_size - z_size; i++){
			z.push_back(0);
		}
	}

	for(int i = z.size() - 1; i >= 0; i--){
		if(z[i] > c[i]){
			return true;
		}
		else if(c[i] > z[i]){
			return false;
		}
	}

	return true;

}

vector<int> AddBandB(vector<int> e, vector<int> f){
	vector<int> sum;
	int carry = 0;	

	int e_size, f_size;

	e_size = e.size();
	f_size = f.size();
	
	if(e_size > f_size){
		for(int i = 0; i < e_size - f_size; i++){
			f.push_back(0);
		}
	}
	else if(f_size > e_size){
		for(int i = 0; i < f_size - e_size; i++){
			e.push_back(0);
		}
	}

	for(int i = 0; i < e.size(); i++){
		int sum2 = e[i] + f[i] + carry;

		if(sum2 == 0){
			carry = 0;
			sum.push_back(0);
		}
		else if(sum2 == 1){
			carry = 0;
			sum.push_back(1);
		}
		else if(sum2 == 2){
			carry = 1;
			sum.push_back(0);
		}
		else if(sum2 == 3){
			carry = 1;
			sum.push_back(1);
		}
	}

	if(carry == 1){
		sum.push_back(1);
	}

	return sum;
}


vector<int> SubtractBandB(vector<int> c, vector<int> d){
	vector<int> diff;

	int d_size, c_size;

	d_size = d.size();
	c_size = c.size();

	if(d_size != c_size){
		for(int i = 0; i < c_size - d_size; i++){
			d.push_back(0);
		}
	}

	int x = 0;

	for(int i = 0; i < c.size(); i++){
		if((x + c[i] + d[i]) % 2 == 1){
			diff.push_back(1);
		}
		else{
			diff.push_back(0);
		}

		if((x + d[i] + diff[i]) >= 2){
			x = 1;
		}
		else{
			x = 0;
		}
	}

	int diff_size;
	diff_size = diff.size();

	for(int i = 0; i < diff_size - 1; i++){
		if(diff[diff_size - (i+1)] == 0){
			diff.pop_back();
		}
		else{
			break;
		}
	}

	return diff;
}


vector<int> MultiplyBandB(vector<int> a, vector<int> b){
	vector<int> z;

	z.push_back(0);

	for(int i = b.size()-1; i > -1; i--){
		z = AddBandB(z, z);
		if(b[i] == 1){
			z = AddBandB(z, a);
		}
	}	

	return z;
}

vector<int> DivideBandB(vector<int> j, vector<int> k, vector<int> &r){
		vector<int> q;
		q.push_back(0);
		r.push_back(0);

		vector<int> one;
		one.push_back(1);

		for(int i = j.size() - 1; i >= 0; i--){
			q = AddBandB(q, q);
			r = AddBandB(r, r);
			if(j[i] == 1){
				r = AddBandB(r, one);
			}
			if(greaterBandB(r, k)){
				r = SubtractBandB(r, k);
				q = AddBandB(q, one);
			}
		}

		return q;
}

vector<int> ModuloExp(vector<int> base, vector<int> exp, vector<int> modulo){
	vector<int> overflow;
	vector<int> output;

	output.push_back(1);

	for(int i = exp.size() - 1; i >= 0; i--){
		output = MultiplyBandB(output, output);
		if(exp[i] == 1) {
			output = MultiplyBandB(output, base);
		}		
		overflow.clear();
		DivideBandB(output, modulo, overflow);
		output = overflow;
	}

	return output;
}

vector<int> SubtractOne(vector<int> x){
	vector<int> minus_one;

	minus_one.push_back(x[0] - 1);
		
	for(int i = 1; i < x.size(); i++){
		minus_one.push_back(x[i]);
	}

	return minus_one;
}

vector<int> By2inDec(vector<int> w){

	//intialize variables
	int carry = 0;
	vector<int> dec_vector;

	for(int i = 0; i < w.size(); i++){
		//create a sum variable that stores the sum of each iteration
		int sum = w[i] + w[i] + carry;

		//if the sum is greater than 9
		if(sum > 9){
			//set the carry to 1
			carry = 1;

			//push back the first digit taking away the 10 carry
			dec_vector.push_back(sum % 10);
		}
		//otherwise if it is 0-9
		else{
			//set the carry to 0
			carry = 0;

			//push back the sum
			dec_vector.push_back(sum);
		}
	}
	
	//if the carry is 1 after the loop
	if(carry == 1){
		//push back the carry by 1
		dec_vector.push_back(1);
	}

	//return the new doubled vector
	return dec_vector;
}

vector<int> BinarytoDecimal(vector<int> bi_vector){
	vector<int> dec_vector; //Vector of decimal values

	for(int i = bi_vector.size() - 1; i > -1; i--){
		//double the current integer that the vector represents
		dec_vector = By2inDec(dec_vector);

		//if v[i] is odd
		if(bi_vector[i] % 2 == 1){
			//if the vector is empty
			if(dec_vector.empty()){
				//push back a 1
				dec_vector.push_back(1);
			}
			//otherwise add 1 to the v[0] location
			else{
				dec_vector[0] += 1;
			}
		}
	}
	return dec_vector;
}

//Function that takes in a number of bits and returns a random generated number with that amount of bits
vector<int> getRandomBinary(int bits){
	//initialize a vector to return
	vector<int> bi;

	//create new random seeds
	//srand(time(NULL));

	//loop through each bit
	for(int i = 0; i < bits; i++){
		//if it's the first bit, make it a 1
		if(i == 0){
			bi.push_back(1);
		}
		//*-------------OPTIONAL IF YOU WANT THE FIRST BIT TO ALSO BE A 1-------------*/
		//if it's the last bit, make it a 1
		//else if(i == bits - 1){
		//	bi.push_back(1);
		//}
		//otherwise randomly generate it
		else{
			bi.push_back(rand() % 2);
		}
	}

	//return the vector with n amount of bits
	return bi;
}	

int main(){

	//initialize variables
	int n;
	int prime_counter = 0;
	int total_counter = 0;
	vector<int> three;
	vector<int> one;
	vector<int> mod;
	vector<int> minus_one;
	vector<int> b_num;

	//create the one and three
	three.push_back(1);
	three.push_back(1);
	three.push_back(0);
	one.push_back(1);
	
	//randomize the seed with the system time
	srand(time(NULL));

	//First generate 100 prime numbers at 16 bits
	while(prime_counter != 100){
		
		//Generate a random binary number with 16 bits
		b_num = getRandomBinary(16);

		//create the exponent for the mod which is b_num - 1
		minus_one = SubtractBandB(b_num, one);

		//Call the ModuloExp function
		mod = ModuloExp(three, minus_one, b_num);

		//if the output is one then it is most likely prime
		if(mod == one){
			
			//Convert it to decimal
			b_num = BinarytoDecimal(b_num);

			//Print it out
			for(int i = 0; i < b_num.size(); i++){
				cout << b_num[b_num.size() - (i+1)];
			}
			
			//increment the prime count
			prime_counter++;

			//deal with spacing
			if(prime_counter == 100){
				cout << endl;
			}
			else{
				cout << ", ";
			}
		}
	
		//increment the total
		total_counter++;
	}	

	//output message
	cout << "Prime numbers generated: " << prime_counter << endl << "Total numbers generated: " << total_counter << endl;

	cout << "---------------------------16 BIT GENERATION---------------------------" << endl;

	//set prime_counter and total_counter back to 0
	prime_counter = 0;
	total_counter = 0;


	//create a clock
	clock_t t;

	t = clock();
	
	//go until you find a prime
	while(prime_counter != 1){

		//Generate a random binary number with 16 bits
		b_num = getRandomBinary(16);

		//create the exponent for the mod which is b_num - 1
		minus_one = SubtractBandB(b_num, one);

		//Call the ModuloExp function
		mod = ModuloExp(three, minus_one, b_num);

		//if the output is one then it is most likely prime
		if(mod == one){
			//Convert it to decimal
			b_num = BinarytoDecimal(b_num);

			//Print it out
			for(int i = 0; i < b_num.size(); i++){
				cout << b_num[b_num.size() - (i+1)];
			}

			//increment the prime count
			prime_counter++;

			cout << endl;
		}

		total_counter++;
	}

	t = clock() - t;
	double secs = double(t) / CLOCKS_PER_SEC;

	cout << "Prime numbers generated: " << prime_counter << endl << "Total numbers generated: " << total_counter << endl << "Execution time: " << secs << " seconds." << endl;

	cout << "---------------------------32 BIT GENERATION---------------------------" << endl;

	//set prime_counter and total_counter back to 0
	prime_counter = 0;
	total_counter = 0;

	t = clock();

	//go until you find a prime
	while(prime_counter != 1){
		
		//Generate a random binary number with 32 bits
		b_num = getRandomBinary(32);

		//create the exponent for the mod which b_num - 1
		minus_one = SubtractBandB(b_num, one);

		//Call the ModuloExp function
		mod = ModuloExp(three, minus_one, b_num);

		//if the output is one then it is most likely prime
		if(mod == one){
			//Convert it to decimal
			b_num = BinarytoDecimal(b_num);

			//Print it out
			for(int i = 0; i < b_num.size(); i++){
				cout << b_num[b_num.size() - (i+1)];
			}
			
			//increment the prime count
			prime_counter++;

			cout << endl;
		}

		total_counter++;
	}

	t = clock() - t;
	secs = double(t) / CLOCKS_PER_SEC;

	cout << "Prime numbers generated: " << prime_counter << endl << "Total numbers generated: " << total_counter << endl << "Execution time: " << secs << " seconds." << endl;

	cout << "---------------------------64 BIT GENERATION---------------------------" << endl;

	//set prime_counter and total_counter back to 0
	prime_counter = 0;
	total_counter = 0;

	t = clock();

	//go until you find a prime
	while(prime_counter != 1){
		
		//Generate a random binary number with 64 bits
		b_num = getRandomBinary(64);

		//create the exponent for the mod which is b_num - 1
		minus_one = SubtractBandB(b_num, one);

		//Call the ModuloExp function
		mod = ModuloExp(three, minus_one, b_num);

		//if the output is one then it is most likely prime
		if(mod == one){
			//Convert it to decimal
			b_num = BinarytoDecimal(b_num);

			//Print it out
			for(int i = 0; i < b_num.size(); i++){
				cout << b_num[b_num.size() - (i+1)];
			}

			//increment the prime count
			prime_counter++;

			cout << endl;
		}

		total_counter++;
	}

	t = clock() - t;
	secs = double(t) / CLOCKS_PER_SEC;

	cout << "Prime numbers generated: " << prime_counter << endl << "Total numbers generated: " << total_counter << endl << "Execution time: " << secs << " seconds." << endl;

	cout << "---------------------------128 BIT GENERATION---------------------------" << endl;

	//set prime_counter and total_counter back to 0
	prime_counter = 0;
	total_counter = 0;

	t = clock();

	//go until you find a prime
	while(prime_counter != 1){
		
		//Genereate a random binary number with 128 bits
		b_num = getRandomBinary(128);

		//create the exponent for the mod which is b_num - 1
		minus_one = SubtractBandB(b_num, one);

		//Call the ModuloExp function
		mod = ModuloExp(three, minus_one, b_num);

		//if the output is one then it is most likely prime
		if(mod == one){
			//Convert it to decimal
			b_num = BinarytoDecimal(b_num);

			//Print it out
			for(int i = 0; i < b_num.size(); i++){
				cout << b_num[b_num.size() - (i+1)];
			}

			//increment the prime count
			prime_counter++;

			cout << endl;
		}

		total_counter++;
	}	

	t = clock() - t;
	secs = double(t) / CLOCKS_PER_SEC;

	cout << "Prime numbers generated: " << prime_counter << endl << "Total numbers generated: " << total_counter << endl << "Execution time: " << secs << " seconds." << endl;

	cout << "---------------------------256 BIT GENERATION---------------------------" << endl;

	//set prime_counter and total_counter back to 0
	prime_counter = 0;
	total_counter = 0;

	t = clock();

	//go until you find a prime
	while(prime_counter != 1){
		
		//Generate a random binary number with 128 bits
		b_num = getRandomBinary(256);

		//create the exponent for the mod which is b_num - 1
		minus_one = SubtractBandB(b_num, one);

		//Call the ModuloExp function
		mod = ModuloExp(three, minus_one, b_num);

		//if the output is one then it is most likely prime
		if(mod == one){
			//Convert it to decimal
			b_num = BinarytoDecimal(b_num);

			//Print it out
			for(int i = 0; i < b_num.size(); i++){
				cout << b_num[b_num.size() - (i+1)];
			}

			//increment the prime count
			prime_counter++;

			cout << endl;
		}	

		total_counter++;
	}

	t = clock() - t;
	secs = double(t) / CLOCKS_PER_SEC;

	cout << "Prime numbers generated: " << prime_counter << endl << "Total numbers generated: " << total_counter << endl << "Execution time: " << secs << " seconds." << endl;

	return 0;
}
