package main.scala
import scala.io.Source._

object Part1 {
  def main(args: Array[String]): Unit = {
    if(args.length<1) {
      println("Pass path to data file as argument")
      return;
    }
    val lines = fromFile(args(0)).getLines
      .map(_.split(": ")).drop(1).flatten
      .map(_.split(" \\| ").toList.map(_.split(" +").toList))
    println(lines mkString "\n")
  }
}
