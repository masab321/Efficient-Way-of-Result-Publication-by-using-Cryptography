package com.example.result;

public class Model {

    String course;
    String grade;
    String credit;

    public Model() {
    }

    public Model(String course, String grade, String credit) {
        this.course = course;
        this.grade = grade;
        this.credit = credit;

    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
    }

    public String getGrade() {
        return grade;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }

    public String getCredit() {
        return credit;
    }

    public void setCredit(String credit) {
        this.credit = credit;
    }
}
