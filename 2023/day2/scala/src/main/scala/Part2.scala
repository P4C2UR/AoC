package main.scala
import scala.io.Source._
import scala.math.max

object Part2 {
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
          })).flatten
            .foldLeft((0,0,0))((acc,x)=>{
              x(1) match
              case 'r' => (max(acc(0),x(0)),acc(1),acc(2))
              case 'g' => (acc(0),max(acc(1),x(0)),acc(2))
              case 'b' => (acc(0),acc(1),max(acc(2),x(0)))
            })))
              .foldLeft(0)((acc,numbered)=>
                  acc+numbered(1)(0)*numbered(1)(1)*numbered(1)(2))
    println(lines)
  }
}
