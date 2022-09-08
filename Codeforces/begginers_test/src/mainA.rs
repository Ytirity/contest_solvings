use std::io;

fn main() -> io::Result<()>{

    let mut input = String::new();
    io::stdin().read_line(&mut input)?;
    let n: i32 = input.trim().parse().unwrap();

    for _i in 0..n {
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        let size: i32 = input.trim().parse().unwrap();
        io::stdin().read_line(&mut input)?;

        println!("{}", solve(size, input));
    }

    Ok(())
}


fn solve(size : i32, str : String) -> &'static str {
    if size != 5 {
        return "NO"
    }

    for i in ['T', 'i', 'm', 'u', 'r'] {
        if !str.contains(i){
            return "NO"
        }
    }

    "YES"
}