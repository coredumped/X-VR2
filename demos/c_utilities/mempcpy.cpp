#include<xvr2.h>

using namespace xvr2;
using namespace std;

const String &print_array(int array[], int elems){
	static String output("");
	int i;
	output.clear();
	for(i = 0; i < elems; i++){
		if(i > 0){
			output.concat(", ");
		}
		output.concat(array[i]);
	}
	return output;
}

int main(int argc, char *argv[]){
	String s1;
	String s2;
	int arr1[] = {0, 1, 2, 3, 4};
	int arr2[] = {5, 6, 7, 8, 9};
	int *arr3;
	int *itmp;
	char *ptr1;
	char *ptr2;
	char *ptr3;
	char *tmp;
	s1 = "hello ";
	s2 = "world";
	ptr1 = s1.toCharPtr();
	ptr2 = s2.toCharPtr();
	ptr3 = new char[s1.size() + s2.size() + 1];
	tmp = Util::mempcpy<char>(ptr3, ptr1, s1.size());
	tmp = Util::mempcpy<char>(tmp, ptr2, s2.size());
	*tmp = '\0';
	cout << "ptr1: " << ptr1 << endl;
	cout << "ptr2: " << ptr2 << endl;
	cout << "ptr3: " << ptr3 << endl;

	arr3 = new int[10];
	itmp = Util::mempcpy<int>(arr3, arr1, 5);
	itmp = Util::mempcpy<int>(itmp, arr2, 5);

	cout << "arr1: " << print_array(arr1, 5) << endl;
	cout << "arr2: " << print_array(arr2, 5) << endl;
	cout << "arr3: " << print_array(arr3, 10) << endl;

	delete[] ptr3;
	delete[] arr3;
	return 0;
}
