/***************************************************************************
 *            main.c
 *
 *  Sat November 16 19:39:39 2013
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

#include<stdio.h>
#include<time.h>
#include"include/structs.h"

#define OFF		0
#define ON		1

/*Prototypes*/
int Enviroment(void);
int UI(void);
int Controls(void);
int FillCtl(void);


int main()
{
	int lowlev, fatal=0, i, cold=ON, bl_seq=OFF, bur_seq=OFF, seq=0;
	time_t blowertv, burnertv, interlocktv;
	
	/*system init and safety assumtions*/
	Enviroment();
	if ((burner[0].state & GRAIN) == GRAIN)
		lowlev = OFF;
	else
		lowlev = ON;

	/*Main Control Loop*/
	while (fatal == 0) {
		Enviroment();
		UI();

		switch (user.state) {
			case F_E: //fill/empty mode
				for (i=0; i<(BLOWERS-1); i++) {
					burner[i].req_state &= (IGNITION | BURNER_ON);
					m_blower[i].state &= (~RUN);
				}
				switch (user.f_e) {
					case FILL:
						FillCtl();
						m_discharge.state &= (~RUN);
						m_meter.state &= (~RUN);
						break;
					case EMPTY:
						m_discharge.state |= RUN;
						m_meter.state |= RUN;
						m_fill.state $= (~RUN);
						break;
					case BYPASS:
						m_discharge.state |= RUN;
						m_meter.state |= RUN;
						FillCtl();
				}
				bl_seq = OFF;
				bur_seq = OFF;
				cold = ON;
				break;

			case BA_SAFE: //safe batch mode
				for (i=0; i<(BLOWERS-1); i++) {
					if (burner[i].fault == 1) {
						user.state = IDLE;
						break;
					}
				}
				break;

			case AU_SAFE: //safe auto mode
				for (i=0; i<(BLOWERS-1); i++) {
					if (burner[i].fault == 1) {
						user.state = IDLE;
						break;
					}
				}
				m_discharge.state &= (~RUN);
				m_meter.state &= (~RUN);
				FillCtl();
				break;
			
			case AUTO: //startup auto mode

			case BATCH: //startup batch mode
				if (cold == ON) {
					time(&blowertv);
					time(&burnertv);
					cold = OFF;
					seq = 0;
				}
				if (bl_seq == OFF) {
					if ((difftime(time(NULL), blowertv)) > BLOWER_SEQ_DELAY) {
						if ((user.blower[seq] & BL_ON) == BL_ON)
							m_blower[seq].state |= RUN;
						time(&blowertv);
						time(&burnertv);
						seq++;
						if (seq == BLOWERS) {
							bl_seq = ON;
							seq = 0;
						}
					}
				} else if (bur_seq == OFF) {
					if ((difftime(time(NULL), burnertv)) > BURNER_SEQ_DELAY) {
						if ((user.blower[seq] & BUR_ON) == BUR_ON) {
							if ((burner[seq].state & IGNITION) != IGNITION)
								burner[seq].req_state |= IGNITION;
							else if ((burner[seq].state&BURNER_ON)!=BURNER_ON)
								burner[seq].req_state |= BURNER_ON;
							else
								seq++;
						} else
							seq++;
						
						if (seq == BLOWERS) {
							bur_seq = ON;
							seq = 0;
							time(&interlocktv);
						}
					}
				} else
					if ((difftime(time(NULL), interlocktv)) > INTERLOCK) {
						user.state = IDLE;
					}
					
				break;

			case default: //idle - everything off
				m_fill.state &= (~RUN);
				m_discharge.state &= (~RUN);
				m_meter.state &= (~RUN);
				for (i=0; i<(BLOWERS-1); i++) {
					burner[i].req_state &= (IGNITION | BURNER_ON);
					m_blower[i].state &= (~RUN);
				}
				bl_seq = OFF;
				bur_seq = OFF;
				cold = ON;
		}

		Controls();
			
	}
}


int Enviroment(void)
{
	/* Dummy function for reading sensors (e_blower variable).
	 * This is where we would populate the system enviroment structures
	 * or inject data for unit testing
	 **/
	
	return 0;
}

int UI(void)
{
	/* Dummy User Interface function (user variable).
	 **/

	return 0;
}

int Controls(void)
{
	/* Dummy motor and burner function
	 * all m_* variables and burner variable
	 **/

	return 0;
}

int FillCtl(void)
{
	/* Dryer fill timing
	 **/
	static time_t updatetv;

	if ((burner[0].state & GRAIN) != GRAIN) { //low
		if ((difftime(time(NULL), updatetv)) > FILL_DELAY)
			m_fill.state |= RUN;
		else
			m_fill.state &= (~RUN);
	} else { //full
		m_fill.state &= (~RUN);
		time(&updatetv);
	}
	return 0;
}
