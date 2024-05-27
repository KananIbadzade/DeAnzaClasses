// Kanan Ibadzade - CIS22C - HW2


using namespace std;
#include <iostream>
#include <fstream>

/*
  The following code file is divided into 4 sections

    1. The interface and code for Class Student  (supplied)
    2. The interface and code for class StudentEsa  (insert your HM1 code here)
    3. The interface and code for class StudentDQI  (The interface is supplied. HM2 is writing the code to implement this interface)
    4. The HM2 test program code (supplied)
*/


// 1.  ************************ class Student code included here  ***************************

class Student
{  

private:
    int sid; 
    string sname; 

public:
    Student() { 
        sid = 0; sname.clear();
    };
    Student(const Student& os) { 
        sid = os.sid;  sname = os.sname;
    };
    Student(int id, string name) { 
        sid = id; sname = name;
    };
    ~Student() { 
        sname.clear();
    };


   
    string getName() { return (sname); };
    int getId() { return (sid); };
};

//      ********************** End class Student ***************************************


// 2.   ********************** Insert "class StudentEsa" code from your homework 1 assignment here


class StudentEsa
{
private:  
    Student** sap; 
    Student** tp;  
    int cnum; 
    int cmz; 

public: 

    void realloc() {
        delete[] tp;
        tp = new Student * [cmz * 2];
        cmz *= 2;
    };

    StudentEsa(int ms)       
    {
        sap = new Student * [ms];
        cmz = ms;
        cnum = 0;
        tp = NULL;
    };


    StudentEsa()                  
    {
        sap = nullptr;
        tp = nullptr;
        cnum = 0;
        cmz = 0;
    };


    StudentEsa(StudentEsa& sep)  
    {
        cnum = sep.cnum;
        cmz = sep.cmz;
        tp = nullptr;
        sap = new Student * [cmz];

    };


    ~StudentEsa()          
    {
        delete[] sap;
    };

    
    int getSize()
    {
        return cnum;
    };


    Student* get(int index)
    {
        if ((index < 0) || (index >= cnum)) {
            return (NULL);
        }
        else {
            return (sap[index]);   
        }
    };


    int set(Student* sep, int index)
    {
        if (index < 0 || index >= cnum) return -1; 

        sap[index] = sep; 
        return index;
    };

   
    int insert(Student* nsp, int index)
    {
        if (index < 0 || index > cnum) return -1;

        if (cnum == cmz) {
            realloc();

            for (int i = 0; i < index; i++) {
                tp[i] = sap[i]; 
            }

            tp[index] = nsp; 

            for (int i = index; i < cnum; i++) {
                tp[i + 1] = sap[i];
            }
            sap = tp;
            tp = NULL;
            cnum++;

            return index;
        }

       
        Student* tempStudent = nsp;
        for (int i = index; i < cnum; i++) {
            Student* tempPtr = sap[i];
            sap[i] = tempStudent;
            tempStudent = tempPtr;
        } 
        sap[cnum] = tempStudent;  

        cnum++;  
        return index;
    };

   
    int remove(int index)
    {
        if (index >= cmz || index < 0) return -1; 
        Student* nsp = sap[index];

        for (int i = index + 1; i < cnum; i++) {   
            sap[i - 1] = sap[i];
        }
        cnum -= 1;
        return index;
    };


    
    int append(Student* nsp)
    {
        return insert(nsp, cnum);
    };


    int prepend(Student* nsp)
    {
        return insert(nsp, 0);
    };
};

//      ********************** End class Student ***************************************


// 3. *************************** Homework 2.  insert the code for the StudentDQI into the StudentDQI interface below ***************


// class "StudentDQI   <Homework #2 - wraps (embeds) Extended Student Array (ESA) so it is invisible to external users of this class

class StudentDQI {
private:
    StudentEsa* soa;  // Allocated Extended Student Array 
    // These might be useful if your solution is for extra credit and positions the DQ in the MIDDLE of the Extended Array
    unsigned int top; // Index value 1 above highest OA element used //front 
    unsigned int btm; // Index value 1 below lowest OA element used  // back
public:
    StudentDQI(unsigned int s)// Create a DQ with this initial size 
    {
        soa = new StudentEsa(s * 2);   // allocates memory for soa and assign to the pointer s
        btm = s + 1;
        top = s;
        for (int i = 0; i <= top; i++) { // initilaze the array with nullptr to the index top
            soa->append(nullptr);
        }
    };

    StudentDQI(StudentDQI& s) // Equate this to an existing DQ (can use private parts directly)
    {
        top = s.top;
        btm = s.btm;
    };
        
    ~StudentDQI() // Destruct the DQI (free OA space)
    {
        delete[] soa;
    };

    int getSize()  // Gets # elements (Student *) in the DQ
    {
        return (btm - top) - 1;
    };
        
    bool isEmpty() // True if no elements held (“pop” will fail)
    {
        if (btm - top == 1) {
            return true;
        }
        else {
            return false;
        }
    };

    int pushFront(Student* s) // Prepend a new element to the front
    {
        soa->set(s, top);
        top--;

        return 0;
    };

    Student* popFront()    // Remove the first element and return it
    {
        if (isEmpty()) {
            return nullptr;
        }
        Student* first = soa->get(top + 1);


        soa->set(nullptr, top + 1);
        top++;

        return first;
    };

    Student* lookFront()    // Return the first element but do not remove it
    {
        return soa->get(top + 1);
    };

    int pushBack(Student* s) // Append a new element to the back
    {
        soa->append(s);
        btm++;

        return btm;
    };

    Student* popBack()     // Remove the last element and return it
    {
        if (isEmpty()) {
            return nullptr;
        }
        Student* last = soa->get(btm - 1);

        soa->set(nullptr, btm);
        btm--;
      
        return last;
    };

    Student* lookBack()    // Return the last element but do not remove it
    {
        return soa->get(btm - 1);
    };
};


// **************************** End class StudentDQI ******************************


// 4.  ***********************  Start of StudentDQI Test Program Code  ************

int main()
{ // Redirect Input
    string infileName; // Use if Input redirected
    string outfileName; // Use if output redirected 
    FILE** input = NULL;  // Recovering Cin

    // Command File Record entries
    int ssize; // Size of extended array
    int nops; // # operations to perform

    char command; // Command (G,Z   F,G,H   B,C,D)
    // Not all of the following are present in each command (Default given)
    int num;  // Student ID Number (-1 default)
    string name;  // Student Name (XXXX default)

    StudentDQI* dqi = NULL;   // Pointer to DeQue
    Student sc; // A class to collect Students is generated

    int x = 0; // Useful variables

    cout << "Use input file:  ";
    cin >> infileName; // Get name of file containing input data
    cout << "Using input file " << infileName << endl << endl;

    // Create an input file stream to read supplied file
    std::ifstream inp;
    inp.open(infileName.c_str());
    if (!inp) {
        cerr << "Error: file " << infileName.c_str() << "  could not be opened" << endl;
        exit(1);
    }

    // First line is array size and # commands to add, every subsequent line is one of:
    // 
    // GetSize:      S / -1 / -1
    // isEmpty:      Z / -1 / -1
    // 
    //  PushFront:   F / Student ID / Student Name
    //  PopFront:    G / -1 / -1
    //  LookFront :  H / -1 / -1
    //
    //  PushBack:    B / Student ID / Student Name
    //  PopBack:     C / -1 / -1
    //  LookBack :   D / -1 / -1

    // Get Size of Extended Array and # of commands
    // ssize is size of extended array, nops is # commands

    inp >> ssize >> nops;
    cout << "Read Array size " << ssize << "  Read # commands " << nops << endl;

    Student* stud;    // Array to hold pointer of created student.
    dqi = new StudentDQI(ssize);  // Create Dequeue of specified size.


    for (int i = 0; i < nops; i++) {  // Process Commands 
        //**************************************************************
        inp >> command;
        inp >> num;
        inp >> name;
        cout << "Command: " << command << "  " << num << "  " << name << endl;

        // Process each command
        switch (command)
        { // Convert to command for Extended Array
        case 'S':  // Get Size
            cout << "Size:  " << dqi->getSize() << endl;
            break;

        case 'Z':  // Check if Empty
            cout << "Empty : " << dqi->isEmpty() << endl;
            break;

        case 'F':  // Push Front
            stud = new Student(num, name);
            (void)dqi->pushFront(stud);
            cout << "Pushed Front " << num << "  " << name << endl;
            break;

        case 'G': // Pop Front
            stud = dqi->popFront();
            if (stud) { // Success
                cout << "Pop Front " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
            break;

        case 'H':  // Look Front
            stud = dqi->lookFront();
            if (stud) { // Success ... don't delete Student
                cout << "Look Front " << stud->getId() << "  " << stud->getName() << endl;
            }
            break;

        case 'B':  // Push Back
            stud = new Student(num, name);
            (void)dqi->pushBack(stud);
            cout << "Pushed Back " << num << "  " << name << endl;
            break;

        case 'C':  // Pop Back
            stud = dqi->popBack();
            if (stud) { // Success
                cout << "Pop Back " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
            break;

        case 'D':  // Look Back
            stud = dqi->lookBack();
            if (stud) { // Success ... don't delete Student
                cout << "Look Back " << stud->getId() << "  " << stud->getName() << endl;
            }
            break;

        default:
            cout << "Illegal Command:  " << command << endl;
        }
    }
    // Print out Current contents of extended array
    x = dqi->getSize(); // Get number of array elements
    cout << "------------------" << endl << "Start Popping from bottom  " << x << "  Elements queued" << endl << endl;

    while (stud = dqi->popBack())
    {
        cout << "Student: ID = " << stud->getId() << "  Name = " << stud->getName() << endl;
    }
    return (0);
};

// **********************************  End of test code  *************************************