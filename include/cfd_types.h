/***************************************************************************
 *            cfd_types.h
 *  Common Data Structure Types
 *
 *  Sat November 16 19:36:07 2013
 *  Copyright  2013  Joel Morgan
 *  <jrcowboy79@gmail.com>
 ****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include"platform.h"


/*=======================*/
/*  Machine Model Types  */
/*=======================*/

/**
 * motor_t
 * type for motor data
 * 
 * int state			flags for motor state
 * int speed			motor rotational speed - (RPM*10)
 * int power			motor power usage - (Watts)
 **/

struct motor_t {
	int state;
	int speed;
	int power;
};

/*motor state flags*/

#define RUN				1
#define OVLD			2
#define RUN_CONFIRM		4
#define PLUG			8

/**
 * enviro_t
 * type for burner enviroment data
 * 
 * int moist			grain moisture (%)
 * int gr_temp			grain temperature (K)
 * int pl_temp			plenum temperature (K)
 * int v_pres			velocity pressure - (Pa gauge)
 * int s_pres			static pressure - (Pa gauge)
 * int t_pres			total pressure - (Pa gauge)
 *
 * Above represented as decimal integers left shifted 2 (*100)
 *
 **/

struct enviro_t {
	int moist;
	int gr_temp;
	int pl_temp;
	int v_pres;
	int s_pres;
	int t_pres;
};

/**
 * burner_t
 * type for burner run state
 * 
 * int state			burner state flags
 * int req_state		burner requested state flags
 * int faults			burner fault flags - 1=general burner fault
 * 
 **/

struct burner_t {
	int state;
	int req_state;
	int fault;
};

/*burner state flags*/
#define IGNITION		1
#define BURNER_ON		2
#define GRAIN			4



/*====================*/
/*  User Model Types  */
/*====================*/

/**
 * user_t
 * type for individual blower user requested state
 * 
 * int state					flags for requested machine state
 * int blower[BLOWERS]			blower(s) requested state array
 * int f_e						flags for requested fill/empty state
 **/

struct user_t {
	int state;
	int blower[BLOWERS];
	int f_e;
};

/*user state flags*/

#define F_E			1
#define BATCH		2
#define AUTO		3
#define BA_SAFE		4
#define AU_SAFE		5

#define BL_ON		1
#define BL_HEAT		2

#define FILL		1
#define EMPTY		2
#define BYPASS		4
