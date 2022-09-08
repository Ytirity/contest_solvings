use std::io;

struct Rect {
    width: usize,
    height: usize,
}

struct Req {
    ins_w: usize,
    ins_h: usize,
    out_w: usize,
    out_h: usize,
}

static mut INSIDE_AREA: [[i64; 1010]; 1010] = [[0; 1010]; 1010];

fn main() -> io::Result<()>{

    let n: usize = {
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        input.trim().parse().unwrap()
    };


    

    for _i in 0..n {

        let rect_n: i64 = read!();

        let req_n: i64 = read!();


        let mut rects = Vec::new();

        for _i in 0..rect_n{
            rects.push(Rect { height: read!(), width: read!() });
        }

        unsafe { save_rects(&rects); }

        for _i in 0..req_n{
            println!( "{}", unsafe {solve(Req {ins_h: read!(), ins_w: read!(), out_h: read!(), out_w: read!()})});
        }

    }

    Ok(())
}

unsafe fn save_rects(rects: &Vec<Rect>) -> (){

    for i in 1..1007 {
        for j in 1..1007 {
                INSIDE_AREA[i][j] = 0;
        }
    }

    for rect in rects {
        INSIDE_AREA[rect.height][rect.width] += (rect.width * rect.height) as i64;
    }

    for i in 1..1005 {
        for j in 1..1005 {
                INSIDE_AREA[i][j] += INSIDE_AREA[i][j - 1];
                INSIDE_AREA[i][j] += INSIDE_AREA[i - 1][j];
                INSIDE_AREA[i][j] -= INSIDE_AREA[i - 1][j - 1];
        }
    }
}


unsafe fn solve(req : Req) -> i64 {
    INSIDE_AREA[req.out_h - 1][req.out_w - 1] + INSIDE_AREA[req.ins_h][req.ins_w] - INSIDE_AREA[req.out_h - 1][req.ins_w] - INSIDE_AREA[req.ins_h ][req.out_w - 1]
}