/*
 * Allegro Image Viewer
 * Allan Legemaate
 * 30/12/2016
 * Made because Windows 10 sucks
 */

// Libs
#include <allegro.h>

// Extentions to support PNG, JPG and GIF
// Allegro handles BMP, TIF and a few others
#include <alpng.h>
#include <jpgalleg.h>
#include <algif.h>
#include <iostream>

#include "globals.h"
#include "state.h"
#include "init.h"
#include "game.h"

// Current state object
state *currentState = NULL;

// Delete game state and free state resources
void clean_up(){
  delete currentState;
}

// Close button handler (enables X button)
volatile int close_button_pressed = FALSE;

void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

// Change game state
void change_state(){
  //If the state needs to be changed
  if( nextState != STATE_NULL ){
    //Delete the current state
    if( nextState != STATE_EXIT ){
        delete currentState;
    }

    //Change the state
    switch( nextState ){
      case STATE_INIT:
        currentState = new init();
        break;
      case STATE_GAME :
        currentState = new game();
        break;
      default:
        currentState = new init();
        break;
    }

    //Change the current state ID
    stateID = nextState;

    //NULL the next state ID
    nextState = STATE_NULL;
  }
}

// Setup game
void setup(){
  // Load allegro library
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse();
  install_joystick(JOY_TYPE_AUTODETECT);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_color_depth(32);

  // Addons
  alpng_init();
  jpgalleg_init();
  algif_init();

  // Close button
  LOCK_FUNCTION(close_button_handler);
  set_close_button_callback(close_button_handler);

  // Game state
  stateID = STATE_NULL;
  nextState = STATE_NULL;
}

// Start here
int main( int argc, char *argv[]){
  // Copy over argc and argv
  number_of_images = argc - 1;

  // Iterate through argv
  for( int i = 1; i < argc; i++){
    image_urls.push_back( std::string(argv[i]));
    std::cout << argv[i] << "\n";
  }

  // Setup basic functionality
  setup();

  //Set the current state ID
  stateID = STATE_INIT;

  //Set the current game state object
  currentState = new init();

  // Run loop
  while( !key[KEY_ESC] && !close_button_pressed){
    currentState -> update();
    currentState -> draw();

    // Check for next state
    change_state();
  }

  //Clean up
  clean_up();

  // End
  return 0;
}
END_OF_MAIN();
