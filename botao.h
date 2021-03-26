class Button
{
	public:
		Button(void);
		void FSM_button();
		bool get_nurse_calling(void);
	
	private:
		bool nurse_calling;
		bool on_off_nurse;
		unsigned char pressed_btn;
		unsigned int time_push_button;	
		unsigned int time_nurse_push_button_in;
		unsigned int time_nurse_push_button_out;
		unsigned int time_to_turn_off;
		unsigned short int state_botao;	
};		
