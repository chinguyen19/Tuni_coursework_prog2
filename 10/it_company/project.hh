/* Class Project
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Class for describing a project in an IT company.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef PROJECT_HH
#define PROJECT_HH

#include "employee.hh"
#include "date.hh"
#include "utils.hh"
#include <string>
#include <map>

const std::string NOT_QUALIFIED = "Not qualified any more: ";

class Project
{
public:
    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as string ddmmyyyy)
     */
    Project(const std::string& id, const std::string& start);

    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as Date object)
     */
    Project(const std::string& id, const Date& start);

    /**
     * @brief Project destructor
     */
    ~Project();

    // More public methods
    const std::string& get_id() const;
    Date get_start_date() const;
    Date get_end_date() const;

    bool is_closed() const;
    void close(const Date& end_date);

    void add_requirement(const std::string& requirement);
    void removeEmployee(Employee* employee);
    void remove_unqualified_employees();
    std::vector<Employee*> get_unqualified_employees() const;
//    void update_staff_qualification();
    bool has_requirements() const;
    bool is_employee_qualified(const Employee* employee) const;
    bool assign_employee(Employee* employee);
    // Function to get the set of requirements for the project
    std::set<std::string> get_requirements() const;

    // Function to check if the project has any staff
    bool has_staff() const;

    // Function to get the vector of staff for the project
    std::vector<Employee*> get_staff() const;

    //Function to check if an employee has been assigned to a particular project
    bool has_employee(const std::string& employee_id) const;
private:
    /**
     * @brief obvious attributes
     */
    std::string id_; // Can be a name or any other identifier
    Date start_;
    Date end_;
    bool closed_ = false;
    // More attributes and private methods
    std::set<std::string> requirements_;
    // Staff members assigned to the project
    std::map<std::string, Employee*> staff_;



};

#endif // PROJECT_HH
