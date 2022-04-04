// Fun little side project I did in a few hours.
// Finds the set of numbers such that X = a * b * c ... * d
// where it's factors are closest

// works by getting the prime factors of the number, sorting and then multiplying the smallest and biggest numbers on the list.

#include <iostream>
#include <vector>
#include <algorithm>

int primelist[] = {	
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
	61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
	139, 149, 151, 157, 163, 167, 173, 179,	181, 191, 193, 197, 199, 211, 223, 227,
	229, 233, 239, 241, 251, 257, 263, 269,	271, 277, 281, 283, 293, 307, 311, 313,
	317, 331, 337, 347, 349, 353, 359, 367,	373, 379, 383, 389, 397, 401, 409, 419,
	421, 431, 433, 439, 443, 449, 457, 461,	463, 467, 479, 487, 491, 499, 503, 509, 
	521, 523, 541 
};

/**
 * @brief Checks if the value X is a prime
 * 
 * @param X the prime
 * @return true the value is a prime
 * @return false the value is not a prime
 */
bool isprime(unsigned int X){
	if(X < 2) return false; // anything less than 2 is not a prime
    if(X == 2) return true;	// two is a prime number
    if(X % 2 == 0) return false; // divisible by 2, e.g. not a prime
    for(int i=3; (i*i)<=X; i+=2){ // from 3 up any even number can be skipped. 
        if(X % i == 0 ) return false; // One of the factorized values of X would always be less than the sqrt(X)
    }
    return true; // passed all the checks, it's a prime.
}

/**
 * @brief divides the number X into it's product of prime factors
 * 
 * @param X the value
 * @param V the buffer to store the prime factors in
 */
void getpopf(unsigned int X, std::vector<int>& V){
	if(isprime(X)){
		V.push_back(X);
		return;
	}
	else{
		int i = 0;
		for(; X % primelist[i]; i++); // get the smallest prime divider with an integer number
		getpopf(X / primelist[i], V);
		V.push_back(primelist[i]);
	}
}

/**
 * @brief gets the greatest common factor of a value
 * 
 * @param popf the product of prime factors of a value
 * @param V the list of greatest common factors
 * @param size the size of the list
 */
void getgcf(std::vector<int> popf, std::vector<int>& V, int size){
	sort(popf.begin(), popf.end());
	if(popf.size() <= size){
		V = popf;
		return;
	}
	size_t popfsize = popf.size();
	for(int i = 0; i < popfsize/2 && i < size; i++){
		popf[i] += popf.back();
		popf.pop_back();
	}
	getgcf(popf, V, size);
}

int main(){
	std::vector<int> popf;
	std::vector<int> gcf;
	getpopf(1080, popf);
	getgcf(popf, gcf, 2);

	for(int i = 0; i < gcf.size(); i++){
		std::cout << gcf[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
