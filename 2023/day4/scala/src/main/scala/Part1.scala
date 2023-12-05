package main.scala
import scala.io.Source._
import scala.math.pow

object Part1 {
  def main(args: Array[String]): Unit = {
    if(args.length<1) {
      println("Pass path to data file as argument")
      return;
    }
    val lines = fromFile(args(0)).getLines
      .map(_.split(": ").drop(1)).flatten
      .map(_.replace('|', ' ').trim.split(" +").map(_.toInt))
      .map(_.groupBy(identity).collect {case (k,v) if v.length>1 => k})
      .map(_.toList.length-1)
      .foldLeft(0)((acc,x)=>acc+pow(2, x).toInt)
    println(lines)
  }
}
