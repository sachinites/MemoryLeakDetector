/*
 * =====================================================================================
 *
 *       Filename:  app.c
 *
 *    Description:  This file represents the application demonstrating the use of MLD library
 *
 *        Version:  1.0
 *        Created:  Thursday 28 February 2019 06:41:32  IST
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:  Er. Abhishek Sagar, Networking Developer (AS), sachinites@gmail.com
 *        Company:  Brocade Communications(Jul 2012- Mar 2016), Current : Juniper Networks(Apr 2017 - Present)
 *        
 *        This file is part of the MLD distribution (https://github.com/sachinites).
 *        Copyright (c) 2017 Abhishek Sagar.
 *        This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU General Public License as published by  
 *        the Free Software Foundation, version 3.
 *
 *        This program is distributed in the hope that it will be useful, but 
 *        WITHOUT ANY WARRANTY; without even the implied warranty of 
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 *        General Public License for more details.
 *
 *        You should have received a copy of the GNU General Public License 
 *        along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * =====================================================================================
 */

#include "mld.h"
#include <memory.h>
#include <stdlib.h>

/*Application Structures*/

typedef struct emp_ {

    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_ *mgr;
    float salary;
} emp_t;


int
main(int argc, char **argv){

    /*Step 1 : Initialize a new structure database */
    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    
    /*Create structure record for structure emp_t*/
    struct_db_rec_t *emp_rec = calloc(1, sizeof(struct_db_rec_t) + (5*sizeof(field_info_t)));
    
    emp_rec->next = NULL;
    strncpy(emp_rec->struct_name, "emp_t", strlen("emp_t"));
    emp_rec->ds_size = sizeof(emp_t);
    emp_rec->n_fields = 5;
    
    /*Field 1 data :*/
    strncpy(emp_rec->fields[0].fname, "emp_name", strlen("emp_name"));
    emp_rec->fields[0].dtype = CHAR;
    emp_rec->fields[0].size = 30;
    emp_rec->fields[0].offset = OFFSETOF(emp_t, emp_name);
    strncpy(emp_rec->fields[0].nested_str_name, "nil", strlen("nil"));
    
    /*Field 2 data :*/
    strncpy(emp_rec->fields[1].fname, "emp_id", strlen("emp_id"));
    emp_rec->fields[1].dtype = UINT32;
    emp_rec->fields[1].size = sizeof(unsigned int);
    emp_rec->fields[1].offset = OFFSETOF(emp_t, emp_id);
    strncpy(emp_rec->fields[1].nested_str_name, "nil", strlen("nil"));
    
    /*Field 3 data :*/
    strncpy(emp_rec->fields[2].fname, "age", strlen("age"));
    emp_rec->fields[2].dtype = UINT32;
    emp_rec->fields[2].size = sizeof(unsigned int);
    emp_rec->fields[2].offset = OFFSETOF(emp_t, age);
    strncpy(emp_rec->fields[2].nested_str_name, "nil", strlen("nil"));
    
    /*Field 4 data :*/
    strncpy(emp_rec->fields[3].fname, "mgr", strlen("mgr"));
    emp_rec->fields[3].dtype = OBJ_PTR;
    emp_rec->fields[3].size = sizeof(void*);
    emp_rec->fields[3].offset = OFFSETOF(emp_t, mgr);
    strncpy(emp_rec->fields[3].nested_str_name, "emp_t", strlen("emp_t"));

    /*Field 5 data :*/
    strncpy(emp_rec->fields[4].fname, "salary", strlen("salary"));
    emp_rec->fields[4].dtype = FLOAT;
    emp_rec->fields[4].size = sizeof(float);
    emp_rec->fields[4].offset = OFFSETOF(emp_t, salary);
    strncpy(emp_rec->fields[4].nested_str_name, "nil", strlen("nil"));

    add_structure_to_struct_db(struct_db, emp_rec);

    print_structure_db(struct_db);
    return 0;
}
