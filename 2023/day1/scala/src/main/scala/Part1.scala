package main.scala
import scala.io.Source._

object Part1 {
  def main(args: Array[String]): Unit = {
    val lines = fromFile("../data").getLines
      .map(line=>line.filter(_.isDigit).toString)
      .foldLeft(0)((acc,digits)=>acc+digits(0).asDigit*10+digits(digits.length-1).asDigit)
    println(lines)
  }
}
