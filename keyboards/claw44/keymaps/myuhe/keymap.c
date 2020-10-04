#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif


extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _DVORAK 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3

enum custom_keycodes
  {
   QWERTY ,
   DVORAK= SAFE_RANGE,
   LOWER,
   RAISE,
   W_ZERO
  };

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Tap Dance Declarations

enum tapstates {
  SINGLE_TAP  = 1,
  SINGLE_HOLD = 2,
  /* LA_SINGLE_TAP  = 1, */
  /* LA_SINGLE_HOLD = 2, */
  /* RA_SINGLE_TAP  = 1, */
  /* RA_SINGLE_HOLD = 2, */
};


enum tapkeys {
  LM_ESC = 0, // enumerator for the tap dance
  LM_LALT, // enumerator for the tap dance
  LM_RALT, // enumerator for the tap dance
};

#define KC_ KC_TRNS
#define KC_RST RESET


#define KC_L_DEL LT(_LOWER, KC_DEL) // lower
#define KC_R_BS LT(_RAISE, KC_BSPC) // raise
#define KC_G_PD LGUI_T(KC_PGDN) // cmd or win */
#define KC_G_PU RGUI_T(KC_PGUP) // cmd or Win */
#define KC_C_BS LCTL_T(KC_BSPC) // ctrl
#define KC_C_ESC LCTL_T(KC_ESC) // ctrl
#define KC_S_SPC LSFT_T(KC_SPC) // SandS left
#define KC_S_ENT RSFT_T(KC_ENT) // SandS right
#define KC_A_MH LALT_T(KC_MHEN) // eisu
#define KC_A_HE RALT_T(KC_HENK) // kana
#define DF_D    DF(_DVORAK)
#define DF_Q    DF(_QWERTY)
#define TD_ESC  TD(LM_ESC)
#define TD_LALT  TD(LM_LALT)
#define TD_RALT  TD(LM_RALT)

#define LM_A_Q(_QWERTY, MOD_LALT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
  //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
     KC_TAB   , KC_Q   , KC_W  , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_C_ESC , KC_A   ,KC_S   , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, KC_QUOT,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_LAPO, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RAPC,
  //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                       KC_A_MH, KC_L_DEL, KC_S_SPC, KC_G_PD,     KC_G_PU, KC_S_ENT, KC_R_BS, KC_A_HE
  //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
  ),

  [_DVORAK] = LAYOUT( \
  //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
     KC_TAB  ,KC_QUOT ,KC_COMM, KC_DOT  , KC_P   , KC_Y     , KC_F   ,    KC_G    , KC_C    , KC_R   , KC_L    , KC_SLSH,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     TD_ESC , KC_A   ,KC_O    , KC_E   , KC_U    , KC_I    ,    KC_D    , KC_H    , KC_T   , KC_N    , KC_S   , KC_MINS,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_LAPO , KC_SCLN   , KC_Q    , KC_J   , KC_K  , KC_X   ,    KC_B    , KC_M    , KC_W   , KC_V    , KC_Z   , KC_RAPC,
  //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                       TD_LALT, KC_L_DEL, KC_S_SPC, KC_G_PD,     KC_G_PU, KC_S_ENT, KC_R_BS, TD_RALT
  //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
  ),

  
  //   \ ^ ! & |  @ = + * % -
  // ( # $ " ' ~  ← ↓ ↑ → ` )
  //         { [  ] }

  [_RAISE] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     _______, KC_BSLS, KC_CIRC, KC_EXLM, KC_AMPR, KC_PIPE,     KC_AT  , KC_EQL , KC_PLUS, KC_ASTR, KC_PERC, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LPRN, KC_HASH, KC_DLR , KC_DQT , KC_QUOT, KC_TILD,     KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_GRV , KC_RPRN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, KC_LCBR, KC_LBRC,     KC_RBRC, KC_RCBR, _______, _______, _______, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______, _______, _______, RESET
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     _______, _______, KC_F7  , KC_F8  , KC_F9  , KC_F12 ,     KC_EQL , KC_7   , KC_8   , KC_9   , KC_LPRN, KC_RPRN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, _______, KC_F4  , KC_F5  , KC_F6  , KC_F11 ,     KC_BSPC, KC_4   , KC_5   , KC_6   , KC_PLUS, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, _______, KC_F1  , KC_F2 , KC_F3   , KC_F10 ,     KC_DOT , KC_1   , KC_2   , KC_3   , KC_SLSH, KC_ASTR,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       RESET  , _______, _______, DF_Q   ,     DF_D   , KC_0   , W_ZERO , _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),
};

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLEjjjD in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case W_ZERO:
          if(record->event.pressed){
        //pressed
      SEND_STRING("00");
    }else{
        //released
      }
      break;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  else return 3;
}


static int lstap_state;

void ls_finished (qk_tap_dance_state_t *state, void *user_data) {
  lstap_state = cur_dance(state);
  switch (lstap_state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD: layer_on(1);register_code(KC_LCTL); break;
  }
}

void ls_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lstap_state) {
    case SINGLE_TAP: unregister_code(KC_ESC); break;
    case SINGLE_HOLD: layer_off(1); unregister_code(KC_LCTL); break;
  }
  lstap_state = 0;
}

static int latap_state;

void la_finished (qk_tap_dance_state_t *state, void *user_data) {
  latap_state = cur_dance(state);
  switch (latap_state) {
    case SINGLE_TAP: register_code(KC_HENK); break;
    case SINGLE_HOLD: layer_on(1);register_code(KC_LALT); break;
  }
}

void la_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (latap_state) {
    case SINGLE_TAP: unregister_code(KC_HENK); break;
    case SINGLE_HOLD: layer_off(1); unregister_code(KC_LALT); break;
  }
  latap_state = 0;
}

static int ratap_state;

void ra_finished (qk_tap_dance_state_t *state, void *user_data) {
  ratap_state = cur_dance(state);
  switch (ratap_state) {
    case SINGLE_TAP: register_code(KC_MHEN); break;
    case SINGLE_HOLD: layer_on(1);register_code(KC_RALT); break;
  }
}

void ra_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ratap_state) {
    case SINGLE_TAP: unregister_code(KC_MHEN); break;
    case SINGLE_HOLD: layer_off(1); unregister_code(KC_RALT); break;
  }
  ratap_state = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [LM_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ls_finished, ls_reset),
  [LM_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,la_finished, la_reset), 
  [LM_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ra_finished, ra_reset), 
};


