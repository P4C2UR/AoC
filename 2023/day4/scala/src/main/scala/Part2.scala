package main.scala
import scala.io.Source._

object Part2 {
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
      .foldLeft((List.fill(10)(1),0))((acc,x)=> {
        val l = acc(0).drop(1) :+ 1
        (l.take(x+1).map(_+1*acc(0)(0)) ::: l.drop(x+1), acc(1)+acc(0)(0))
      })(1)
    println(lines)
  }
}
