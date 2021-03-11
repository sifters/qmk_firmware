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
  _COLEMAK,
  _GAME,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;


enum custom_tapdances{
  TD_LCTRL_NUMPAD = 0,
  TD_CAPS_LOCK,
};

#define T_LCTRL     TD(TD_LCTRL_NUMPAD)     // Tap/hold for CTL, double tap for NUMPAD
#define T_LSFT		TD(TD_CAPS_LOCK)		// Tap/Hold for Left Shift, Triple Tap for Capslock

#define KC_TASK     LCTL(LSFT(KC_ESC))
#define KC_CADL     LCTL(LALT(KC_DEL))
#define KC_DTTO     LCTL(KC_GRAVE)
#define KC_ATAB     LALT(KC_TAB)
#define TL_LWR      LT(_LOWER, KC_SPC)
#define TL_RSE      LT(_RAISE, KC_SPC)
#define MT_QUOT     MT(MOD_RCTL, KC_QUOT)
#define MT_BSLS     MT(MOD_RSFT, KC_BSLS) 

#define BL_QWER     DF(_QWERTY)
#define BL_GAME     DF(_GAME)
#define BL_CLMK     DF(_COLEMAK)

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
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |Enter |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,   \
  T_LCTRL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT_QUOT,  \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT_BSLS,  \
                        KC_LALT, KC_LGUI, MO(_LOWER), TL_LWR,  TL_RSE,   KC_ENT,  KC_BSPC, KC_DEL \
),
/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | GESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |Enter |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT( \
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  \
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_EQL,   \
  T_LCTRL,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     MT_QUOT,  \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_LBRC, KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  MT_BSLS,  \
                        KC_LALT, KC_LGUI, MO(_LOWER), TL_LWR,  TL_RSE,   KC_ENT, KC_BSPC,  KC_DEL \
),
/* Game
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | GESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |Enter |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_GAME] = LAYOUT( \
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,   \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT_QUOT,  \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT_BSLS,  \
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC,  TL_RSE,   KC_ENT,  KC_BSPC, KC_DEL \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | DTTO | TASK | CADL |      |      |      |                    |      |      |      |      |      | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ATAB |      |      |      |      |      |                    | PGUP | Home |  Up  | End  |      | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| PGDN | PIPE | Down | Right|      | Enter|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | CAPS |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |Enter |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_DTTO, KC_TASK, KC_CADL, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, \
  KC_ATAB, _______, _______, _______, _______, _______,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, KC_DEL,  \
  _______, _______, _______, _______, _______, _______,                   KC_PGDN, KC_PIPE, KC_DOWN, KC_RGHT, XXXXXXX, KC_ENT,  \
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______, _______, _______, _______\
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
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |Enter |RAISE |BackSP| DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |      |
 *                   `----------------------------'           '------''---------------------------'
 */

[_RAISE] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, KC_PSCR, \
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  _______, _______, KC_WBAK, KC_WSTP, KC_WFWD, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______, _______, _______, _______\
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |QWERTY|      |      |      |      |      |                    | MAIL | CALC |      | MSEL | MPLY | VOL+ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | GAME |      |      |      |      |      |                    |      |      |      | MPRV | MNXT | VOL- |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |COLEMK|      |      |      |      |      |-------.    ,-------| BRIU |      |      |      |      | MUTE |
 * |------+------+------+------+------+------| Power |    | Sleep |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| BRID |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |Enter |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  BL_QWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MAIL, KC_CALC, XXXXXXX, KC_MSEL, KC_MPLY, KC_VOLU, \
  BL_GAME, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_VOLD, \
  BL_CLMK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PWR,  KC_SLEP, KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                             _______, _______, _______, _______, _______, _______, _______, _______ \
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
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |  P0  |  .   |      |
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

layer_state_t layer_state_set_user(layer_state_t state) {
// Set ADJUST layer
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    switch (get_highest_layer(state)) {
    case _NUMPAD:
		if ( !(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
  			register_code(KC_NUMLOCK);
    		unregister_code(KC_NUMLOCK);
  		};
        break;
    default: //  for any other layers, or the default layer
		if ( (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
  			register_code(KC_NUMLOCK);
    		unregister_code(KC_NUMLOCK);
  		};
        break;
    }
  return state;
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


void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    //oled_write_ln(read_layer_state(), false);
     oled_write_P(PSTR("Layout: "), false);
     switch (biton32(default_layer_state)) {
         case _QWERTY:
             oled_write_P(PSTR("QWERTY\n"), false);
             break;
         case _COLEMAK:
             oled_write_P(PSTR("Colemak\n"), false);
             break;
         case _GAME:
             oled_write_P(PSTR("Game\n"), false);
             break;
         default:
             oled_write_P(PSTR("Undefined "), false);
        } 
    oled_write_P(PSTR("Layer: "), false);
    switch(get_highest_layer(layer_state)) {
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
            oled_write_P(PSTR("Default\n"), false);
    }       
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ?       PSTR("NUM ")   : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ?      PSTR("CAP ")   : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ?    PSTR("SCR \n") : PSTR("    \n"), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE


void dance_capslock(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
		tap_code(KC_CAPS);
        reset_tap_dance(state);
    } else {
        tap_code(KC_LSFT);
        reset_tap_dance(state);
    }
}


// All tap dance functions would go here.

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTRL_NUMPAD] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LCTRL, _NUMPAD),
    [TD_CAPS_LOCK] = ACTION_TAP_DANCE_FN(dance_capslock),
};
