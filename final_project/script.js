function myFunction() {
    // Get the checkbox
    var checkBox = document.getElementById("detect");
    // Get the output text
    var text = document.getElementById("p2");

    // If the checkbox is checked, display the output text
    if (checkBox.checked == true){
      text.style.display = "inline-block";
    } else {
      text.style.display = "none";
    }
  }