package main.scala
import scala.io.Source._

object Part1 {
  def main(args: Array[String]): Unit = {
    if(args.length<1) {
      println("Pass path to data file as argument")
      return;
    }
    val lines = fromFile(args(0)).getLines
      .map(line=>line.split(": "))
      .map(labeled=>(labeled(0).split(" ")(1).toInt,labeled(1)))
      .map(numbered=>(numbered(0),
        numbered(1).toString().split("; ").toList
          .map(game=>game.split(", ").toList
          .map(color=>{
            val s = color.split(" ")
            (s(0).toInt,s(1)(0))
          })).flatten))
      .filter(x=>{
        x(1).map(x=>
        x(1) match
        case 'r' => x(0)<=12
        case 'g' => x(0)<=13
        case 'b' => x(0)<=14)
        .foldLeft(true)((acc,x)=>acc&&x)
      })
      .foldLeft(0)((acc,x)=>acc+x(0))
    println(lines)
  }
}
