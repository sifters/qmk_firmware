#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum tapdance_types{
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum custom_tapdances{
  TD_LCTRL_NUMPAD = 0,
};

#define T_LCTRL    TD(TD_LCTRL_NUMPAD)     // Tap for Y, double tap for NUMPAD

#define KC_TASK     LCTL(LSFT(KC_ESC))
#define KC_DTTO     LCTL(KC_GRAVE)
#define KC_ATAB     LALT(KC_TAB)
#define TL_LWR      LT(_LOWER, KC_SPC)
#define TL_RSE      LT(_RAISE, KC_SPC)
#define MT_BSLS     MT(MOD_RSFT, KC_BSLS) 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | GESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,   \
  T_LCTRL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT_BSLS,  \
                        KC_LALT, KC_LGUI, MO(_LOWER), TL_LWR,  TL_RSE,   KC_ENT, KC_BSPC, KC_DEL \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | DTTO |      |      |      |      |      |                    |      |      |      |      |      | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ATAB |      |      |      |      |      |                    | PGUP | Home |  Up  | End  |      | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| PGDN | Left | Down | Right|      | Enter|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_DTTO, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, \
  KC_ATAB, _______, _______, _______, _______, _______,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, KC_DEL,  \
  _______, _______, _______, _______, _______, _______,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_ENT,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | BTN2 | MS_U | BTN1 | WH_U |                    | PGUP | Home |  Up  | End  |      | PSCR |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | MS_L | MS_D | MS_R | WH_D |-------.    ,-------| PGDN | Left | Down | Right|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | WBAK | WSTP | WFWD |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, KC_PSCR, \
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  _______, _______, KC_WBAK, KC_WSTP, KC_WFWD, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | TASK |      |      |      |      |      |                    |      |      |      | MSEL | MPLY | VOL+ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      | VOL- |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| BRIU |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| BRID |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_MSEL, KC_MPLY, KC_VOLU, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_BRIU, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  ),
/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |      |  /   |   *  |  -   | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |      |      |      |      |      |                    |      |  P7  |  P8  |  P9  |  +   | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCTRL|      |      |      |      |      |-------.    ,-------|      |  P4  |  P5  |  P6  |  .   | KPENT|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |  P1  |  P2  |  P3  |  =   |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |  P0  |  .   |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_NUMPAD] = LAYOUT( \
  KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS, KC_BSPC, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_DEL,  \
  T_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PCMM, KC_PENT, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, XXXXXXX, \
                             _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, _______ \
  )
};

// Set ADJUST layer
uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
// const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    //oled_write_ln(read_layer_state(), false);
    oled_write_P(PSTR("Layer: "), false);
    switch(get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Number Pad\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }       
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

// Begin Tap Dances
int cur_dance (qk_tap_dance_state_t *state) {
   if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTRL_NUMPAD] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LCTRL, _NUMPAD),
};
