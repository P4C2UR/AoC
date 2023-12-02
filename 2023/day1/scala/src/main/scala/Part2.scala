package main.scala
import scala.io.Source._


/*
 * Not working because exercise requires you
 * to parse some numbers starting at the back and
 * some starting at the front which in turn
 * requires parsing it manually
 * It's too much work
 */

object Part2 {
  def main(args: Array[String]): Unit = {
    if(args.length<1) {
      println("Pass path to data file as argument")
      return;
    }
    val lines = fromFile(args(0)).getLines
      .map(line=>line
      .replace("one",   "1")
      .replace("two",   "2")
      .replace("three", "3")
      .replace("four",  "4")
      .replace("five",  "5")
      .replace("six",   "6")
      .replace("seven", "7")
      .replace("eight", "8")
      .replace("nine",  "9")
      .filter(_.isDigit).toString)
      .foldLeft(0)((acc,digits)=>acc+digits(0).asDigit*10+digits(digits.length-1).asDigit)
    println(lines)
  }
}
