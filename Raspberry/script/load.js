//datas
 
  var rows = [];
  rows.push(["Seconde","Temperature"]);
  

   var datas = [];

   var donnee = 0;
   var second = 0;

  var app = angular.module('myApp', []);

  app.controller('myCtrl', function($scope) {

      $scope.donnee = donnee;

      var inter = setInterval(function(){ 
      gettemp();  
      $scope.donnee = donnee;
      //console.log(donnee);
      $scope.$apply();
  

      }, 1000);

          
  });
  
  



  // Load Charts and the corechart and barchart packages.
    google.charts.load('current', { 'packages': ['table','corechart', 'controls']}); 
     // google.charts.setOnLoadCallback(drawChart);

      function drawChart() {
        var data = google.visualization.arrayToDataTable(rows);

        var options = {
            
          curveType: 'function',
           width: 900,
          height: 500,
          legend: { position: 'bottom' },
           /*hAxis: {
                title: 'Seconde'
          },*/
          vAxis: {
            title: '° Celcius',
            
          }
        };

        var chart = new google.visualization.LineChart(document.getElementById('line_chart'));

        chart.draw(data, options);
      }
      

      



$(function(){ //If web page is fully loaded

  i2c();
  gettemp(); 
  action(0); // overwrite Action.txt with 0
    
    //setTimeout(function(){ drawChart();; }, 1000); // Draw the chart after 1 second
    
      var interi2c = setInterval(function(){ 
     i2c(); 
      
      //console.log("get temp");

      }, 500);
    

    var inter = setInterval(function(){ 
      gettemp();  
      
      //console.log("get temp");

      }, 1000);

    var interchart = setInterval(function(){ 
      drawChart();

      }, 1000);
     

  // Show the graph
      $("#line_temp").collapse("show");
      $("#graph").collapse("show");
      $("#piechart_contain").collapse("hide");
      
  // Hide show Graph

    
      $("#switch_light").click(function(){
        alert("All light on");
        //ledon(18);
      
      //document.getElementById("#light1_checked").checked = true;
      $("#light1_checked").prop('checked','checked');
     

      })
      

      $("#light1_checked").change(function() {
        if( $(this).prop('checked'))
        {
          action(1); // Led 1 On
          //alert("Led 1 on");
          
        }else
        {
          action(2);// Led 1 off
          //alert("Led 1 off");
          
        }
      })

        $("#light2_checked").change(function() {
        if( $(this).prop('checked'))
        { 
           action(3); // Led 2 On
          //alert("Led 2 on");
         
        }else
        {
          action(4);// Led 2 off
          //alert("Led 2 off");
        }
      })

        $("#door_checked").change(function() {
        if( $(this).prop('checked'))
        { 
           action(5); // Door Open
          alert("Be carful the Door is open ");
         
        }else
        {
          action(6);// Door Close
          alert("Door is close");
        }
      })

      $("#load_btn").click(function(){
          //loadData();
          //alert("Charged");
      });



  });

function loadData(){
     content = $("#data_content").val();
     //var json_data = JSON.parse(content);  //  Datas de la saisis
    

      rows = [];
      console.log(content);
    
       $.ajax({
            type: "POST",
            url: "/static/json/",
            timeout: 2000,
            contentType : 'application/json',
            data: content,
            success: function(data) {
                //show content
                // alert('Success!'); 
                
            },
            error: function(jqXHR, textStatus, err) {
                //show error message
                alert('text status '+textStatus+', err '+err)
            }
          
        });
        setTimeout(function(){ 

          showData();
          //alert('Success!'); 
        }, 2000);
        
       

}

function showData()
{

   
          $.getJSON("data/data.json", function(data) {

              datas = [];
             
              $.each(data, function(key, val) { // For Each a and b
                  $.each(val, function(date, dateValue) { // For Each date in a and b
                      if (datas[key]) {
                          datas[key] += dateValue;
                      } else {
                          datas[key] = dateValue;
                      }

                      var year = date.split('-')[0]; // Récuparation de l'année
                      var month = date.split('-')[1]; // Récuparation du mois jan = 0


                    
                      
                        // Somme des années
                          if (datas[key+"_"+year]) {
                            datas[key+"_"+year] += dateValue;
                        } else {
                            datas[key+"_"+year] = dateValue;
                        } 
                      
                         //Somme des mois
                         if (datas[key+"_"+year+"_"+month]) {
                            datas[key+"_"+year+"_"+month] += dateValue;
                        } else {
                            datas[key+"_"+year+"_"+month] = dateValue;
                        } 


                      });
                  
                  });
              

              //console.log(datas);
              
              // Création du Tableaux
              rows.push(["Name","Value"]);
              for (var key in datas) {
                  if (datas.hasOwnProperty(key)) {
                      //console.log(key + " -> " + datas[key]);
                      rows.push([key, datas[key]]);  
                  }
              }
              //console.log(rows);

              //drawChart();
              drawVisualization();
              
            
            });
         
}

 function action(number){
 
        
      $.get("data/action.php?value="+number, function(data, status){
        //console.log("data/action.php?value="+number);
        
      });
 
}

function i2c(){

        
  $.get("data/final.php", function(data, status){
    //console.log("data/action.php?value="+number);
    
  });
 

}

  
 

 function gettemp()
 {

    $.get("data/tmp.php", function(data, status){
      //console.log(data);
        donnee = data;
        
         // Création du Tableaux
              
          
        //console.log(key + " -> " + datas[key]);
        //rows.push([second.toString(), parseInt(donnee)]);  
        rows.push(["", parseInt(donnee)]);  
      
        //console.log(rows);
        second = second +1;

             
        
                 
      });
 }
    







  