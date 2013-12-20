/***************************************************************************
 *            structs.h
 *  Common Dryer Data Structures
 *
 *  Wed November 20 16:57:51 2013
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

#include"cfd_types.h"

/*Motor Structures*/
struct motor_t m_blower[BLOWERS];
struct motor_t m_fill;
struct motor_t m_discharge;
struct motor_t m_meter;


/*Blower/Burner Structures*/
struct enviro_t e_blower[BLOWERS];
struct burner_t burner[BLOWERS];


/*User Requested State Structure*/
struct user_t user;
