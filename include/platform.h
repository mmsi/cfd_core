/***************************************************************************
 *            platform.h
 *  Dryer Platform Specific Configuration
 *
 *  Wed November 20 10:07:10 2013
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

/*number of blowers*/
#define BLOWERS		8

/*fuel type*/
#define LPG			0
#define NG			1
#define FUEL		LPG

/*timers*/
#define FILL_DELAY			150
#define BLOWER_SEQ_DELAY	5
#define BURNER_SEQ_DELAY	1
#define INTERLOCK			60


/**
 * blower_t
 * per blower configuation type
 * 
 * int conf			flags for equipment present on blower
 * int max_flow		maximum airflow at no static pressure (m^2/minute)
 * int max_burn		maximum rated burner output (KJ/Hr)
 * int holding		grain holding capacity (L)
 **/

struct blower_t {
	int conf;
	int max_flow;
	int max_burn;
	int holding;
};

/*per blower equipment configuration flags*/
#define CONF_BURNER			(1 << 0)
#define CONF_GRAIN			(1 << 1)
#define CONF_MOIST			(1 << 2)

/*Dryer Platform Array*/
struct blower_t platform[BLOWERS];

/**
 * Platform Buildup
 * 
 * Normally this would be built dynamically by the machine operator. However we
 * will assume a standard configuration with the following code.
 **/

/*setup all blowers with burners and standard settings*/
for (int i=0; i<(BLOWERS-1); i++) {
	platform[i].conf = CONF_BURNER;
	platform[i].max_flow = 708; //assuming 25,000CFM
	platform[i].max_burn = 6330335; //assuming 6 MMBTU/Hr)
	platform[i].holding = 28191; //assuming 800 bu
}

/*setup first and last burner with moisture sensors*/
platform[0].conf |= CONF_MOIST;
platform[BLOWERS-1].conf |= CONF_MOIST;

/*setup first blower with grain switch*/
platform[0].conf |= CONF_GRAIN;
