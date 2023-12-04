#include "project.hh"
#include "utils.hh"
#include "company.hh"
#include "employee.hh"
#include <iostream>
#include <string>
#include <map>


Project::Project(const std::string& id, const std::string& start):
    id_(id), start_(start)
{
}

Project::Project(const std::string& id, const Date &start):
    id_(id), start_(start)
{
}

Project::~Project()
{
    //std::cout << "Project " << id_ << " destructed." << std::endl;
}

const std::string &Project::get_id() const
{
    return id_;
}

Date Project::get_start_date() const
{
    return start_;
}

Date Project::get_end_date() const
{
    if (is_closed()) {
       return end_;
    } else {
        return Date();
    }

}

bool Project::is_closed() const
{
    return closed_;
}

void Project::close(const Date& end_date)
{
       closed_ = true;
       end_ = end_date;
}

void Project::add_requirement(const std::string &requirement)
{
        requirements_.insert(requirement);            

}

void Project::removeEmployee(Employee *employee)
{
    // Check if the employee is in the project
    auto iter = staff_.find(employee->get_id());
    if (iter != staff_.end()) {
        staff_.erase(iter);
    }
}

void Project::remove_unqualified_employees()
{
    std::vector<Employee*> unqualifiedEmployees;

    for (const auto& staffEntry : staff_) {
        Employee* employee = staffEntry.second;

        // Check if the employee has at least one required skill
        bool qualified = !has_requirements() || is_employee_qualified(employee);

        if (!qualified) {
            unqualifiedEmployees.push_back(employee);
        }
    }

    // Remove unqualified employees from the project
    for (Employee* employee : unqualifiedEmployees) {
        removeEmployee(employee);
    }
}

std::vector<Employee*> Project::get_unqualified_employees() const {
    std::vector<Employee*> unqualifiedEmployees;

    for (const auto& staffEntry : staff_) {
        Employee* employee = staffEntry.second;

        // Check if the employee has at least one required skill
        bool qualified = false;
        for (const std::string& requirement : requirements_) {
            if (employee->has_skill(requirement)) {
                qualified = true;
                break;
            }
        }

        if (!qualified) {
            unqualifiedEmployees.push_back(employee);
        }
    }

    return unqualifiedEmployees;
}

bool Project::has_requirements() const {
    return !requirements_.empty();
}

bool Project::is_employee_qualified(const Employee* employee) const {
    if (!has_requirements()) {
        return true;  // No requirements, so any employee is qualified
    }

    for (const std::string& requirement : requirements_) {
        if (employee->has_skill(requirement)) {
            return true;
        }
    }

    return false;  // Employee doesn't have any required skills
}

bool Project::assign_employee(Employee* employee) {
    if (!is_employee_qualified(employee)) {
        return false;  // Employee is not qualified for the project
    }

    if (closed_) {
        return false;  // Can't assign to a closed project
    }
        staff_.insert({employee->get_id(), employee});
        return true;  // Assignment successful
}

std::set<std::string> Project::get_requirements() const
{
    return requirements_;
}

bool Project::has_staff() const
{
    return !staff_.empty();
}

std::vector<Employee *> Project::get_staff() const
{
    std::vector<Employee*> staff_vector;

    for (const auto& staffEntry : staff_) {
        staff_vector.push_back(staffEntry.second);
    }

    return staff_vector;
}

bool Project::has_employee(const std::string& employee_id) const
{
    return staff_.find(employee_id) != staff_.end();
}


