package main.scala
import scala.io.Source._

object Part1 {
  def main(args: Array[String]): Unit = {
    if(args.length<1) {
      println("Pass path to data file as argument")
      return;
    }
    val lines = fromFile(args(0)).getLines
      .map(line=>line.filter(_.isDigit).toString)
      .foldLeft(0)((acc,digits)=>acc+digits(0).asDigit*10+digits(digits.length-1).asDigit)
    println(lines)
  }
}
