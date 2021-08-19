#![no_std]
#![no_builtins]
#![crate_type = "staticlib"]
#![allow(dead_code)]

#[panic_handler]
fn my_panic(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}

extern "C" {
    #[no_mangle]
    static mut led_animation_id: u8;
}

#[no_mangle]
pub extern "C" fn matrix_scan_user() {

}

#[no_mangle]
pub extern "C" fn matrix_init_user() {
    unsafe {
        led_animation_id = 1;
    }
}

#[no_mangle]
static keymaps: [[[u16; 3]; 2]; 1] = [
  [
    [1, 2, 3],
    [4, 5, 6],
  ],
];
