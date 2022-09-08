use std::io;

fn main() -> io::Result<()>{

    let n: usize = {
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        input.trim().parse().unwrap()
    };

    for _i in 0..n {

        let val: i64 = {
            let mut input1 = String::new();
            io::stdin().read_line(&mut input1)?;
            input1.trim().parse().unwrap()
        };
        solve (val);
    }

    Ok(())
}



fn solve(val : i64) -> () {
    let mut left = val;

    match left % 4 {
        0 => {print!("0 "); print!("1 "); left -= 2;},
        1 => {print!("0 "); left -=1},
        2 => {print!("4 "); print!("1 "); print!("2 "); print!("12 "); print!("3 "); print!("8 "); left -= 6;}, // хммм
        3 => {print!("1 "); left -=1},
        _ => (),
    }

    let mut counter = 14;

    while left > 0 {
        print!("{} ", counter);
        counter = counter + 1;
        print!("{} ", counter);
        counter = counter + 1;
        left = left - 2;
    }
    println!("");
}