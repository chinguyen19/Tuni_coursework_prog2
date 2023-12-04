#include "company.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Company::Company()
{
}

Company::~Company()
{
    //std::cout << "Company destructor" << std::endl;

    // TODO: Deallocate staff
    for (auto& staffEntry : all_staff_) {
        delete staffEntry.second;
    }
    // TODO: Deallocate projects
    for (auto& projectEntry : projects_) {
        delete projectEntry.second;
    }
}

void Company::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not Utils::is_numeric(day, false) or
        not Utils::is_numeric(month, false) or
        not Utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not Utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::recruit(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);

    if( iter != current_staff_.end() )
    {
        std::cout << ALREADY_EXISTS << employee_id << std::endl;
        return;
    }

    iter = all_staff_.find(employee_id);
    if( iter != all_staff_.end() )
    {
        current_staff_.insert(*iter);
        iter->second->update_resigned();
        std::cout << EMPLOYEE_RECRUITED << std::endl;
        return;
    }

    Employee* new_employee = new Employee(employee_id);
    all_staff_.insert({employee_id, new_employee});
    current_staff_.insert({employee_id, new_employee});
    std::cout << EMPLOYEE_RECRUITED << std::endl;
}

void Company::leave(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);
    if( iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    iter->second->resign();
    current_staff_.erase(iter); // Employee still stays in all_staff_    
    std::cout << EMPLOYEE_LEFT << std::endl;
}

void Company::add_skill(Params params)
{
    std::string employee_id = params.at(0);
    std::string skill_name = params.at(1);

    // Checks if the employee_id given exists
    std::map<std::string, Employee*>::const_iterator
            staff_iter = current_staff_.find(employee_id);
    if( staff_iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    staff_iter->second->add_skill(skill_name);
    std::cout << SKILL_ADDED << employee_id << std::endl;
}

void Company::print_current_staff(Params)
{
    if( current_staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for( auto employee : current_staff_ )
    {
        employee.second->print_id("");
        std::cout << std::endl;
    }
}

void Company::create_project(Params params)
{
    std::string id = params[0];
    // Check if a project with the given id already exists
    auto project_iter = projects_.find(id);
    if (project_iter != projects_.end()) {
        std::cout << ALREADY_EXISTS << id << std::endl;
        return;
    }

    // Create a new project with the current date as the start date
    Date start_date(Utils::today);
    Project* new_project = new Project(id, start_date);

    // Add the new project to the map
    projects_[id] = new_project;

    std::cout << PROJECT_CREATED << std::endl;

}

void Company::close_project(Params params)
{
    std::string id = params[0];

    // Check if the project exists
    auto project_iter = projects_.find(id);
    if (project_iter == projects_.end()) {
            std::cout << CANT_FIND << id << std::endl;
            return;
    }

    Project* project = project_iter->second;

    // Close the project and set the end date to the current value of today
    project->close(Utils::today);

    std::cout << PROJECT_CLOSED << std::endl;
}

void Company::print_projects(Params)
{
    if (projects_.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for (const auto& project_entry : projects_) {
            const Project* project = project_entry.second;
            std::cout << project->get_id() << " : " ;
            project->get_start_date().print();
            std::cout << " - ";

            // Print end date for closed projects
            if (project->is_closed()) {
                project->get_end_date().print();
            }

            std::cout << std::endl;
        }
    }
}

void Company::add_requirement(Params params)
{
    if (params.size() < 2) {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }

    std::string project_id = params[0];
    std::string requirement = params[1];

    // Checks if the project exists
    auto project_iter = projects_.find(project_id);
    if (project_iter == projects_.end()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project* project = project_iter->second;

    if (project->is_closed()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    // Add the requirement to the project
    project->add_requirement(requirement);    

    // Print unqualified employees
    const std::vector<Employee*>& unqualifiedEmployees = project->get_unqualified_employees();
    if (!unqualifiedEmployees.empty()) {
        std::cout << "Not qualified any more: ";

        auto iter = unqualifiedEmployees.begin();
        std::cout << (*iter)->get_id();

        ++iter;

        for (; iter != unqualifiedEmployees.end(); ++iter) {
            std::cout << ", " << (*iter)->get_id();
        }

        project->remove_unqualified_employees();
        std::cout << std::endl;
    }

    std::cout << REQUIREMENT_ADDED << project_id << std::endl;
}

void Company::assign(Params params)
{

    std::string employee_id = params[0];
    std::string project_id = params[1];

    auto employee_iter = current_staff_.find(employee_id);
    auto project_iter = projects_.find(project_id);

    // Checks if the employee and the project are found in the database
    if (employee_iter == current_staff_.end() || project_iter == projects_.end()) {
        std::cout << CANT_FIND << (employee_iter == current_staff_.end() ? employee_id : project_id) << std::endl;
        return;
    }

    Employee* employee = employee_iter->second;
    Project* project = project_iter->second;


    // Check if the employee is already assigned to the project
    if (project->has_employee(employee_id)) {
        std::cout << CANT_ASSIGN << employee_id << std::endl;
        return;
    }

    // Check if the employee has at least one required skill
    if (!project->has_requirements() || project->is_employee_qualified(employee)) {
        if (project->assign_employee(employee)) {
            std::cout << STAFF_ASSIGNED << project_id << std::endl;
            active_staff_.insert(current_staff_[employee_id]);
        } else {
            std::cout << CANT_ASSIGN << employee_id << std::endl;
        }
    } else {
        std::cout << CANT_ASSIGN << employee_id << std::endl;
    }
}

void Company::print_project_info(Params params)
{
    std::string project_id = params[0];
    auto project_iter = projects_.find(project_id);

    if (project_iter == projects_.end()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project* project = project_iter->second;

    std::cout << project->get_id() << " : ";
    project->get_start_date().print();
    std::cout << " - ";

    if (project->is_closed()) {        
        project->get_end_date().print();
    }

    std::cout << std::endl << "** Requirements: ";

    // Checks if the project has requirements
    if (project->has_requirements()) {
        auto requirements = project->get_requirements();
        auto iter = requirements.begin();

        std::cout << *iter;

        ++iter;

        for (; iter != requirements.end(); ++iter) {
            std::cout << ", " << *iter;
        }
    } else {
        std::cout << "None";
    }

    std::cout << std::endl << "** Staff: ";

    // Checks if the project has staffs assigned
    if (project->has_staff()) {
        auto staff = project->get_staff();
        auto iter = staff.begin();

        std::cout << (*iter)->get_id();

        ++iter;

        for (; iter != staff.end(); ++iter) {
            std::cout << ", " << (*iter)->get_id();
        }
    } else {
        std::cout << "None";
    }

    std::cout << std::endl;
}

void Company::print_employee_info(Params params)
{
    std::string employee_id = params[0];

    // Check if the employee exists
    auto employee_iter = all_staff_.find(employee_id);
    if (employee_iter == all_staff_.end() || employee_iter->second == nullptr || employee_iter->second->has_resigned()) {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    Employee* employee = employee_iter->second;

    // Print skills
    employee->print_skills();

    // Print projects
    std::cout << "Projects: ";
    bool projectsPrinted = false;

    for (const auto& project_entry : projects_) {
        Project* project = project_entry.second;

        // Check if the employee has been assigned to the project
        if (project->has_employee(employee_id)) {
            if (!projectsPrinted) {
                projectsPrinted = true;
            }
            std::cout << std::endl;
            std::cout << "** " << project->get_id() << " : ";

            // Check if the employee has not resigned
            if (!employee->has_resigned()) {
                project->get_start_date().print();
                std::cout << " - ";
                if (project->is_closed()) {
                    project->get_end_date().print();
                } else {
                    std::cout << std::endl;
                }
            }
        }
    }

    if (!projectsPrinted) {
        std::cout << "None" << std::endl;
    }
}

void Company::print_active_staff(Params)
{
    if (active_staff_.empty()) {
        std::cout << "None" << std::endl;
    } else {
        // Sort the active staff alphabetically
        std::vector<const Employee*> sortedActiveStaff(active_staff_.begin(), active_staff_.end());
        std::sort(sortedActiveStaff.begin(), sortedActiveStaff.end(), [](const Employee* a, const Employee* b) {
            return a->get_id() < b->get_id();
        });
        for (const Employee* employee : sortedActiveStaff)
        {
            employee->print_id("");
            std::cout << std::endl;
        }
    }
}
