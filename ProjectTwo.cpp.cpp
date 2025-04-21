//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Karen Schick
// Description : This program supports the Computer Science department at ABCU by
//               providing a simple advising tool.  It reads course data from a CSV
//               file and loads it into a vector data structure. Users can view all
//               courses in alphanumeric order or search for a specific course.
//
//============================================================================

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

/**
 * @brief Converts all characters to uppercase
 * @return string s
 */
std::string toUpperCase(std::string s)
{
    // Convert all characters to upper case
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                   { return std::toupper(c); });

    return s;
}

/**
 * @class Course
 * @brief Represents an ABCU college course with a course number, course name and prerequisites
 */
class Course
{
private:
    string courseNumber;          // Unique identifier for the course
    string courseName;            // Name of course
    vector<string> prerequisites; // List of courseNumbers that are prerequisites for the course

public:
    /**
     * @brief Constructor to initialize Course object with a courseNumber and courseName
     * @param courseNumber The unique identifier of the course
     * @param courseName The name of the course
     */
    Course(string courseNumber, string courseName)
    {
        this->courseNumber = courseNumber;
        this->courseName = courseName;
    }

    /**
     * @brief Adds a prerequisite to the course's list of prerequisites.
     * @param prerequisite The courseNumber of a prerequisite course to add
     */
    void addprerequisites(string prerequisite)
    {
        // add prerequisite to prerequisites vector
        prerequisites.push_back(prerequisite);
    }

    /**
     * @brief Checks if given prequisite is a course at ABCU
     * @param prerequisite the courseNumber of a prerequisite course to validate
     * @param courses The vector of all available courses to check against
     * @return True if prerequisite exists in course list, false if does not exist
     */
    bool validatePrerequisite(string &prerequisite, vector<Course> &courses)
    {
        // Iterate through each course in the list
        for (Course &course : courses)
        {
            // If courseNumber matches prerequisite
            if (course.courseNumber == prerequisite)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Getter for the course number
     * @return The courseNumber of the course
     */
    string getCourseNumber()
    {
        return courseNumber;
    }

    /**
     * @brief Getter for the course name
     * @return The courseName of the course
     */
    string getCourseName()
    {
        return courseName;
    }

    /**
     * @brief Getter for the prerequisite of the course
     * @return A vector of course numbers that are prerequisites for the course
     */
    vector<string> getPrerequisites()
    {
        return prerequisites;
    }
};

/**
 * @brief Reads course data from CSV file and returns vector of Course object.
 * @return vector<Course> A list of all valid courses from CSV file
 */
vector<Course> importDataFile()
{
    vector<Course> courses; // Create empty vector Course to store all courses
    ifstream inFS;          // Input file stream

    // Open input file
    inFS.open("C:\\Users\\gekal\\projects\\ABCUCourseList\\CS 300 ABCU_Advising_Program_Input.csv");

    // Check if the file failed to open
    if (!inFS.is_open())
    {
        cout << "Could not open CS 300 ABCU_Advising_Program_Input.csv" << endl;
        return courses; // Return empty vector courses if file can't be opened
    }

    string line;

    // Read and process each line from input file
    while (getline(inFS, line))
    {
        stringstream ss(line); // Create a stringstream from the line
        string value;
        vector<string> values; // Store individual values

        // Split the line by the commas and store each value
        while (getline(ss, value, ','))
        {
            values.push_back(value);
        }
        // Check if line has at least two values
        if (values.size() < 2)
        {
            // continue to next line if invalid format
            continue;
        }
        else
        {
            // Set first item of values to courseNumber
            string courseNumber = values[0];
            // Set second item of values to courseName
            string courseName = values[1];

            // Create new Course object with extracted courseNumber and courseName
            Course course(courseNumber, courseName);

            //  Iterate through each subsequent item in values
            for (size_t i = 2; i < values.size(); i++)
            {
                // If item not empty
                if (!values[i].empty())
                {
                    // Add item to temporary prerequisites list
                    course.addprerequisites(values[i]);
                }
            }
            // Add course object to courses vector
            courses.push_back(course);
        }
    }
    // Close input file
    inFS.close();

    // Validate that each prerequisites exisits in course list
    // Iterate through each course in the list
    for (Course &course : courses)
    {
        vector<string> validPrerequisites; // Store individual valid prerequisites

        // Iterate through each prerequisite for the current course
        for (string &prerequisite : course.getPrerequisites())
        {
            // if prerequisite is found in course list, it is valid
            if (course.validatePrerequisite(prerequisite, courses))
            {
                // add prerequisite to validPrerequisites vector
                validPrerequisites.push_back(prerequisite);
            }
            else
            {
                // Output message for invalid prerequiste
                cout << "Not a prerequisite for " << course.getCourseNumber() << endl;
            }
        }
    }
    return courses;
};

/**
 * @brief Searches for course from list of courses. Looks through the vector of courses
 * to find the one with matching course number. If found, prints course name and prerequisites
 * @param courses The vector of all available courses to check against
 * @param courseNumber The unique identifier of the course
 */
void searchCourse(vector<Course> &courses, string courseNumber)
{
    // Iterate through each course in the list
    for (Course &course : courses)
    {
        // If the course is the same as courseNumber
        if (course.getCourseNumber() == courseNumber)
        {
            cout << endl;
            // Print out the course information
            cout << course.getCourseNumber() << " - " << course.getCourseName() << endl;

            vector<string> prereqs = course.getPrerequisites();

            // If there are any prequisites
            if (!prereqs.empty())
            {
                cout << "Prerequisites: ";
                // Iterate through elements and print the prerequisite course information
                for (size_t i = 0; i < prereqs.size(); i++)
                {
                    cout << prereqs[i]; // prints prerequisite at index i
                    // If current item is not the last one
                    if (i < prereqs.size() - 1)
                    {
                        cout << ", "; // Prints comma if not last item
                    }
                }
                cout << endl;
            }
            return;
        }
    }
    // If no course was found, print error message
    cout << "Course " << courseNumber << " not found" << endl;
};

/**
 * @brief displays all courses in alpanumberic order based on course number. Performs a selections sort on the vector of Course objects and prints the sorted course numbers along with the course names.
 * @param courses The vector of all available courses to check against
 */
void displaySortedCourse(vector<Course> &courses)
{

    // Get total number of courses
    size_t coursesSize = courses.size();

    // Selection sort algorithm
    // Iterate throught each position except for the last
    for (size_t pos = 0; pos < coursesSize - 1; ++pos)
    {
        size_t min = pos; // Assume current position has the smallest course

        // loop over remaining elements to the right of position finding the smallest course number in the unsorted portion
        for (size_t i = pos + 1; i < coursesSize; ++i)
        {
            // If this element's title is less than minimum title
            if (courses[i].getCourseNumber() < courses[min].getCourseNumber())
            {
                min = i; // Update index of the new minimum
            }
        }
        // Swap the smallest found course with current position if needed
        if (min != pos)
        {
            swap(courses[pos], courses[min]);
        }
    }

    cout << endl;
    // Iterate through each course in the list
    for (Course &course : courses)
    {
        // Print each course's number and name
        cout << course.getCourseNumber() << " - " << course.getCourseName() << endl;
    }
};

/**
 * @brief The main entry point of the program
 * @return 0 Returns 0 when successful
 */
int main()
{
    // Define a vector to hold all courses
    vector<Course> courses;

    // Initalize choice to 0
    int choice = 0;

    // while choice is not 4
    while (choice != 4)
    {
        // Display menu options
        cout << endl;
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Search for a course" << endl;
        cout << "  4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // Handle invalid input
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number 1-4." << endl;
            cin.clear();                                         // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            continue;                                            // Restart the loop
        }

        // Read user input into choice
        switch (choice)
        {
        case 1:
        { // Load file data into datastructure
            courses = importDataFile();
            break;
        }

        case 2:
        { // Display all courses in alphanumeric order by course number
            displaySortedCourse(courses);
            break;
        }

        case 3:
        { // Prompt user to enter course number
            string courseNumber = " ";
            cout << "Enter course number: ";
            cin >> courseNumber;
            courseNumber = toUpperCase(courseNumber); // convert input to upper case
            // Print course title and prerequisites for course number
            searchCourse(courses, courseNumber);
            break;
        }

        case 4:
        { // Exit the program
            break;
        }

        default:
        { // No case matches
            cout << endl;
            cout << "Please enter valid option" << endl;
            break;
        }
        }
    }
    cout << "So long." << endl;
    return 0;
}
