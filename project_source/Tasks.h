/*
 * TASKS : this source file will contain tasks        *
 ******************************************************/
/*
 *****************************************************
 * TEMP_SENSING : in this function we will get the tem*
 * -perature from ADC every 100ms 
 *  NOTE ---> we call this function from TEMP_CONTROL 
 *  to calculate  the average the temperature 
 *****************************************************
*/
unsigned char temp_sensing();
/*
 *****************************************************
 * TEMP_SETTING : in this function we determine the value 
 * of Wanted_Tmp, if pressed UP_SW or DOWN_SW we will enter 
 * the setting mode hence every press will change the Wanted_Tmp
 * by 5 degree.
 * If no switch pressed within 5 seconds we will exit setting 
 * mode  (this check is done in SEV_SEG_DISP function)
 * -----> in setting mode the SEV_SEG dispaly Wanted_Tmp 
 *  with blink behaviour 
 *****************************************************
 */
void temp_setting();
/*
 *****************************************************
 * TEMP_CONTROL : this is the main function that control 
 * the behavior based on the temperature 
 * first we record every 10 temperature reading obtained by
 * TEMP_SENSING then we calculate the average 
 * after that  we call TEMP_CHECKER to determeine which
 * module should be turned on to achieve the desiered temp
 *****************************************************
 */
void temp_control();
/*
 *****************************************************
 * TEMP_CHECKER : in this function we compare the Cur_Tmp
 * to the Wanted_Tmp, and according to the result we turn
 * on the heater or the cooler 
 *****************************************************
 */
void temp_checker();
/*
 *****************************************************
 * ON_OFF_TOGGLE : this function will toggle the system on or
 * off 
 * in on state ---> we retrieve the data from the epprom then 
 * start Crude_Os Tick 
 * in off state ----> we stop Crude_Os Tick and turn off all 
 * the modules in the system 
 *****************************************************
 */
void on_off_toggle();
/*
 ************************************************************
 * SEV_SEG_DISP : this function control SEV_SEG behavior 
 * behavior1 ----> display the Cur_tmp
 * behavior2 ----> dispaly the Wanted_Tmp when in temperature
 * setting mode with blinking effect
 * behavior3 ----> check if UP or DOWN SW is not pressed for 
 * 5 sec if yes exit temperature setting mode and save the 
 * value of Wanted_Tmp in eeprom 
 * NOTE ------> it use SEV_SEG_ACTION to facilitate its work 
 ************************************************************
 */
void sev_seg_disp();
/*
 ************************************************************
 * CLEAR_DISP : this function turn off SEV_SEG display when 
 * in off_state
 * !!!!!!UPDATE ---> this is obslete function and is replaced 
 * whih OFF_STAT_ACTION
 ************************************************************
 */
void clear_disp();
/*
 ************************************************************
 *  OFF_STAT_ACTION : this function turn off all the modules 
 *  when on OFF_STAT 
 ************************************************************
 */
void off_stat_action();
/*
 ************************************************************
 * SEV_SEG_ACTION : it is called by SEV_SEG_DISP with the value
 * it should display associated with whether it should blink
 * or not 
 ************************************************************
 */
void sev_seg_action(unsigned char );
/*
 ************************************************************
 * HEAT_ELEMENT_INDICATOR : it control the statue of led indicator
 * status 1 ----> blink when heating element is on 
 * status 2 ----> constntly on  when cooling element is on 
 * status 3 ----> off when both of them is off
 ************************************************************
 */
void heat_element_indicator();
 /************************************************************
 ************************************************************/
void get_data_from_eprom();
void set_data_to_eprom();
void my_delay();
__bit delay_on_off_toggle();
