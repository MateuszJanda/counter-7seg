#![no_std]
#![no_main]

use arduino_hal::hal::port::Dynamic;
use arduino_hal::port::Pin;
use arduino_hal::port::mode::Output;
use panic_halt as _;

const NUM_OF_SEGMENTS: usize = 7;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

      let mut segments = [
        pins.d2.into_output().downgrade(),
        pins.d3.into_output().downgrade(),
        pins.d4.into_output().downgrade(),
        pins.d5.into_output().downgrade(),
        pins.d6.into_output().downgrade(),
        pins.d7.into_output().downgrade(),
        pins.d8.into_output().downgrade(),
    ];

    let add_button = pins.d9.into_pull_up_input();
    let sub_button = pins.d10.into_pull_up_input();

    let seg_values = [
        [1, 1, 1, 1, 1, 1, 0],
        [1, 1, 1, 1, 1, 1, 0],
    ];


    let mut counter = 0;
    let mut add_pressed = false;
    let mut sub_pressed = false;


    loop {
        display_digit(counter, &mut segments, &seg_values);

        if add_button.is_low() && !add_pressed {
            add_pressed = true;
            if counter < 9 {
                counter +=1;
            }
        } else if add_button.is_high() && add_pressed {
            add_pressed = false;
        }


        if sub_button.is_low() && !sub_pressed {
            sub_pressed = true;
            if counter > 0 {
                counter -= 1;
            }
        } else if sub_button.is_high() && sub_pressed {
            sub_pressed = false;
        }

        arduino_hal::delay_ms(100);
    }
}

fn setup() {

}

fn display_digit(digit: i32, segments: &mut [Pin<Output, Dynamic>; NUM_OF_SEGMENTS], seg_values: &[[i32; NUM_OF_SEGMENTS]; 2]) {
    if digit < 0 || digit > 9 {
        panic!("Out of range");
    }

    for i in 0..NUM_OF_SEGMENTS {
        if seg_values[digit as usize][i] == 0 {

            segments[i].set_low();
        } else {

            segments[i].set_high();
        }
    }
}