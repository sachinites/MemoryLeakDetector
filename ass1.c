/*
 * =====================================================================================
 *
 *       Filename:  ass1.c
 *
 *    Description:  This file explains the asignemt on MemoryLeak Detector Library
 *
 *        Version:  1.0
 *        Created:  Wednesday 13 March 2019 08:53:16  IST
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:  Er. Abhishek Sagar, Networking Developer (AS), sachinites@gmail.com
 *        Company:  Brocade Communications(Jul 2012- Mar 2016), Current : Juniper Networks(Apr 2017 - Present)
 *
 *        Rest of My Udemy Courses are at : https://csepracticals.wixsite.com/csepracticals
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

#include <stdio.h>
#include <stdlib.h>
#include "mld.h"
#include "LinkedList/LinkedListApi.h"

/*Compile the assignment */
/*
gcc -g -c mld.c -o mld.o
gcc -g -c LinkedList/LinkedListApi.c -o LinkedList/LinkedListApi.o
gcc -g -c ass1.c -o ass1.o
gcc -g -o exe1 ass1.o LinkedList/LinkedListApi.o mld.o
./exe1
*/

typedef struct student_ {
    char stud_name[32];
    ll_t *book_lst;  /*List of books borrowed by this student*/
    struct student_ *left;
    struct student_ *right;
} student_t ;


typedef struct university_ {
    student_t *student_lst;
} university_t; 

typedef struct book_ {
    char book_name[32];
    float price;
    student_t *stud; /*Student who borrowed this book*/
    struct book_ *left;
    struct book_ *right;
} book_t; 

typedef struct section_ {
    char section_name[32];
    book_t *book_list;   /* Doubly linked list of books in this section */
} section_t; 

typedef struct library_ {
    char lib_name[32];
    section_t *sections[2];
} library_t;    


void
init_register_application_structures_with_mld(object_db_t *object_db){
    
    /* In this function you should write code to register all application
     * related data structures above with mld library*/
    static field_info_t student_t_fields[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, book_lst, OBJ_PTR,  ll_t),
        FIELD_INFO(student_t, left, OBJ_PTR, student_t),
        FIELD_INFO(student_t, right, OBJ_PTR, student_t)
    };
    REG_STRUCT(object_db->struct_db, student_t, student_t_fields);

    static field_info_t university_t_fields[] = {
        FIELD_INFO(university_t, student_lst, OBJ_PTR, student_t)
    };
    REG_STRUCT(object_db->struct_db, university_t, university_t_fields);

    static field_info_t book_t_fields[] = {
        FIELD_INFO(book_t, book_name, CHAR, 0),
        FIELD_INFO(book_t, price, FLOAT, 0),
        FIELD_INFO(book_t, stud, OBJ_PTR, student_t),
        FIELD_INFO(book_t, left, OBJ_PTR, book_t),
        FIELD_INFO(book_t, right, OBJ_PTR, book_t)
    };
    REG_STRUCT(object_db->struct_db, book_t, book_t_fields);
    

    static field_info_t section_t_fields[] = {
        FIELD_INFO(section_t, section_name, CHAR, 0),
        FIELD_INFO(section_t, book_list, OBJ_PTR, book_t)
    };
    REG_STRUCT(object_db->struct_db, section_t, section_t_fields);

    static field_info_t library_t_fields[] = {
        FIELD_INFO(library_t, lib_name, CHAR, 0),
        FIELD_INFO(library_t, sections, OBJ_PTR, section_t)
    };
    REG_STRUCT(object_db->struct_db, library_t, library_t_fields);    
}

/*
 *
Write a Menu Driven Program as follows :
1.  Search a particular book in Library 
    >> Take a book name in library and search in both sections if book is present or not.

2.  Assign book to Student          
    >> Take two inputs : book name and student name. If both exists, allocate book to student. Report error if book is already borrowed by some other student already.

3.  De-assign book              
    >> Take one Input : book name., and mark it as unborrowed and available to be borrowed

4. Delete book
    >> Take one input : Book name. Delete the book from the library only if found and not assigned to any student.

5. Delete a student
    >> Take one input : student name. Delete the student from university, and release all books borrowed by him/her

6. Run MLD Algorithm

7. Report Leaked Objects

8.  Exit                    
    >> clean up the entire application state and exit the program
*/

static void
main_menu(object_db_t *object_db, university_t *univ, library_t *lib){

    /*Your Main Menu goes here*/
    
}

int 
main(int argc, char **argv){

    /*Create mld structure and object database*/
     struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
     object_db_t *object_db = calloc(1, sizeof(object_db_t));
     object_db->struct_db = struct_db;

    /*Please provide the implmentation of below function*/
     init_register_application_structures_with_mld(object_db);

     /* Now that since, Linkedlist also being used by the application, 
      * Linkedlibrary use standard functions for memory allocations. Check
      * LinkedListApi.c. So, MLD library will not be able to track objects 
      * such as linkedlist or linkedlist nodes. To enable MLD library to
      * track Linkedlist specific objects, we need to do the following :
      * 1. In LinkedListApi.c, define below function and write code to
      * register LinkedList structures with MLD library
      * 2. Replace all standard calloc/malloc/free in LinkedListApi.c with xcalloc and xfree
      * 3. declare a static variable - "static object_db_t *object_db" in LinkedListApi.c and initialize it in below API*/
     init_register_linked_list_structures_with_mld(object_db);

     /*Instantiate a library*/
     library_t *lib = xcalloc(object_db, "library_t", 1);
     /*Library is a root object*/
     mld_set_dynamic_object_as_root(object_db, lib);

     /*Instantiate a University*/
     university_t *univ = xcalloc(object_db, "university_t", 1);
     /*university_t is a root object*/
     mld_set_dynamic_object_as_root(object_db, univ);

     main_menu(object_db, univ, lib);
    return 0;
}
