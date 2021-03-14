#include <queue>
//for simplicity use raw arrays instead of vectors etc...
int *gale_shapley(int **hosp_pref, int **stud_pref, int n)
{
	int hospital[n] = { 0 };
	int *student    = new int[n]; //will be returned so it is made in the heap
	int hospital_next_prefered[n] = { 0 };
	int student_rank[n][n];
	std::queue<int> free_hospitals;
	
	for (int i = 0; i < n; ++i) {
		free_hospitals.push(i); //push the free hospital in the q
		hospital[i] = -1; //set -1 to mean not assigned anywhere
		student [i] = -1;
		
		
		for (int j = 0; j < n; ++j) {
			student_rank[i][stud_pref[i][j]] = j; //create the opposite arrays for the students
		}
	}
	
	while (!free_hospitals.empty()) {
		int free_hospital    = free_hospitals.front();//get the top free hospital
		int prefered_student = hosp_pref[free_hospital][hospital_next_prefered[free_hospital]++];
		//get that hospitals next favorite student
		
		if (hospital[prefered_student] == -1) {
			//if the student is free set them in that hospital
			hospital[prefered_student] = free_hospital;
			student [free_hospital]    = prefered_student;
			free_hospitals.pop(); //hospital is no longer free
		
		} else if (student_rank[prefered_student][free_hospital] < student_rank[prefered_student][hospital[prefered_student]]) {
			//else if the student wants to move to the new hospital
			free_hospitals.push(hospital[prefered_student]); //add the old hospital to the free q
			student [hospital[prefered_student]] = -1; //set the old pair as free
			hospital[prefered_student] = -1;
			
			hospital[prefered_student] = free_hospital; //add the new pair
			student [free_hospital]    = prefered_student;
			free_hospitals.pop(); //the new hospital is no longer free
			
		}
	}
	return student; //return the resulting array
}
