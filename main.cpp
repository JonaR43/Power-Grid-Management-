#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
struct district{
   string name, type, technicians[10];
   int num_resident, power, num_technician;
   bool has_power;
};

void load(string fname, district districts[], int &num, int &power){
   ifstream fin(fname);
   fin >> power;
   fin >> num;
   fin.ignore();
   for (int i = 0; i < num; i++){
      getline(fin, districts[i].name);
      getline(fin, districts[i].type);
      fin >> districts[i].num_resident;
      fin >> districts[i].power;
      fin >> districts[i].has_power;
      fin >> districts[i].num_technician;
      fin.ignore();
      for(int j = 0; j < districts[i].num_technician; j++){
         getline(fin, districts[i].technicians[j]);
      }
   }
   fin.close();
}

void sort(district districts[], int &num){
   for(int i = 0; i < num - 1; i++){
      if(districts[i].num_resident > districts[i+1].num_resident){
         district tempName = districts[i];
         districts[i] = districts[i+1];
         districts[i+1] = tempName;
      }
   }
}

void save(string fname, district districts[], int num, int power){
   ofstream fout(fname);
   fout << power << endl;
   fout << num << endl;
   for(int i = 0 ; i < num; i++){
      fout << districts[i].name << endl;
      fout << districts[i].type << endl;
      fout << districts[i].num_resident << endl;
      fout << districts[i].power << endl;
      fout << districts[i].has_power << endl;
      fout << districts[i].num_technician << endl;
      if(districts[i].num_technician != 0){
         if(districts[i].num_technician == 1){
            fout << districts[i].technicians[0] << endl;
         }
         else{
            for(int j = 0; j < districts[i].num_technician; j++){
               fout << districts[i].technicians[j] << endl;
            }
         }
      }
   }
}

void print_all(district districts[], int num, int power){
   cout << "The current power supply is " << power << "MW." << endl;
   for(int i = 0 ; i < num; i++){
      cout << districts[i].name << endl;
      cout << "District type: " << districts[i].type << endl;
      cout << "Number of residents: " << districts[i].num_resident << endl;
      if(districts[i].has_power == true){
         cout << "Power use: " << districts[i].power << "MW" << endl;
      }
      else{
         cout << "Power use: " << 0 << "MW" << endl;
      }
      cout << "Has power: " << districts[i].has_power << endl;
      if(districts[i].num_technician > 0){
         cout << "Technicians: ";
         if(districts[i].num_technician < 2){
            cout << districts[i].technicians[0] << endl;
         }
         else{
            for(int j = 0; j < districts[i].num_technician; j++){
               if(j < districts[i].num_technician - 1){
                  cout << districts[i].technicians[j] << ", ";
               }
               else{
                  cout << districts[i].technicians[j];
               }
            }
            cout << endl;
         }
      }
      cout << "---" << endl;
   }
   int sum = 0;
         for(int i = 0; i < num; i++){
            if(districts[i].has_power == true){
               sum += districts[i].power;
            }
         }
         if (sum > power){
            cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply " << sum << "MW of power demand. Please shut off one or more districts." << endl;
            cout << "---" << endl;
         }
}

void cut_power(string nameC, district districts[], int size){
   int count = 0;
   for(int i = 0; i < size; i++){               
      if(districts[i].name == nameC){
         districts[i].has_power = false;
         //districts[i].power = 0;
         cout << "The district's power has been successfully turned off." << endl;
         break;
      }
      else{
         count++;
      }
   }
   if(count == size){
      cout << "Error! The district with that name doesn't exist." << endl;
   }
}

void restore_power(string nameC, district districts[], int size){
   int count = 0;
   for(int i = 0; i < size; i++){               
      if(districts[i].name == nameC){
         districts[i].has_power = true;
         //districts[i].power = 100;
         cout << "The district's power has been successfully turned back on." << endl;
         break;
      }
      else{
         count++;
      }
   }
   if(count == size){
      cout << "Error! The district with that name doesn't exist." << endl;
   }
}

void assign_technician(string tech_name, string district_name, district districts[], int num_district){
   int count = 0;
   for(int i = 0; i < num_district; i++){
      if(districts[i].name == district_name){
         districts[i].num_technician++;
         for(int j = districts[i].num_technician - 1 ; j < districts[i].num_technician; j++){
            districts[i].technicians[j] = tech_name;
            cout << "Technician assigned!" << endl;
            return;
         }
      }
      count++;
   }
   if(count == num_district){
      cout << "Error! The district with that name doesn't exist." << endl;
   }
}

int main (){
   //declare vars
   district District;
   string fileName, fileNameOut;
   int total_power, num_districts;
   district arr[10];

   //get the file to open
   cout << "Please enter the name of the file to load:" << endl;
   cin >> fileName;
   
   //open file
   ifstream fin(fileName);
   if(!fin.is_open()){
      cout <<"Error" << endl;
      return 1;
   }
   
   fin >> total_power;
   fin >> num_districts;
   
   //load data
   load(fileName, arr, num_districts, total_power);
   sort(arr, num_districts);
   save(fileNameOut, arr, num_districts, total_power);   
   print_all(arr, num_districts, total_power);
   int option = 0;
   while (!(option == 8)){
      cout << "Main Menu" << endl;
      cout << "1- Status" << endl;
      cout << "2- Set Power Supply" << endl;
      cout << "3- Shutoff Power" << endl;
      cout << "4- Restore Power" << endl;
      cout << "5- Assign Technician" << endl;
      cout << "6- Save" << endl;
      cout << "7- Load" << endl;
      cout << "8- Exit" << endl;
      cout << "Please enter your choice:" << endl;
      cin >> option;
      
      if(option == 1){
         print_all(arr, num_districts, total_power);
      }
      else if (option == 2){
         int new_power;
         cout << "Enter the updated power supply in megawatts:" << endl;
         cin >> new_power;
         total_power = new_power;
      }
            
      else if(option == 3){
         string nameD;
         cout << "Enter the name of the district:" << endl;
         cin.ignore();
         getline(cin, nameD);
         cut_power(nameD, arr, num_districts);
      }
            
      else if(option == 4){
         string nameC;
         cout << "Enter the name of the district:" << endl;
         cin.ignore();
         getline(cin, nameC);
         restore_power(nameC, arr, num_districts);
      }
      
      else if(option == 5){
         string techName, districtName;
         cout << "Enter the name of the technician:" << endl;
         cin.ignore();
         getline(cin, techName);
         cout << "Enter the name of the district to assign them to:" << endl;
         getline(cin, districtName);
         assign_technician(techName, districtName, arr, num_districts);
         
      }
      else if(option == 6){
         
         cout << "Enter the file name to save to:"<< endl;
         cin >> fileNameOut;
         save(fileNameOut, arr, num_districts, total_power);
      }
      else if(option == 7 ){
         cout << "Enter the file name to load from:" << endl;
         cin >> fileName;
         load(fileName, arr, num_districts, total_power);
      }
      else if(option == 8){
      }
   }
   return 0;
}
